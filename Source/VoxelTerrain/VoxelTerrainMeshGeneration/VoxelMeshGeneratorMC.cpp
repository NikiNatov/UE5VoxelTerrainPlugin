#include "VoxelMeshGeneratorMC.h"

FVoxelMeshGeneratorMC::FVoxelMeshGeneratorMC(const FIntVector2& chunkGridPos, const FMarchingCubesParams& mcParams, TQueue<FVoxelChunkData>& outputQueue, FCriticalSection& outputQueueLock)
    : ChunkGridPosition(chunkGridPos), MarchingCubesParams(mcParams), OutputQueue(outputQueue), OutputQueueLock(outputQueueLock)
{
}

void FVoxelMeshGeneratorMC::DoWork()
{
	if (!IsValid(MarchingCubesParams.SurfaceShapeGenerator))
		return;

	bool hasWater = false;

	// Generate noise density map
	TArray<float> densityMap;
	densityMap.SetNumZeroed((MarchingCubesParams.ChunkSize.X + 1) * (MarchingCubesParams.ChunkSize.Y + 1) * (MarchingCubesParams.ChunkSize.Z + 1));

	for (int32 z = 0; z < MarchingCubesParams.ChunkSize.Z + 1; z++)
	{
		for (int32 y = 0; y < MarchingCubesParams.ChunkSize.Y + 1; y++)
		{
			for (int32 x = 0; x < MarchingCubesParams.ChunkSize.X + 1; x++)
			{
				float sampleX = (float)x / MarchingCubesParams.ChunkSize.X + ChunkGridPosition.X;
				float sampleY = (float)y / MarchingCubesParams.ChunkSize.Y + ChunkGridPosition.Y;
				float sampleZ = (float)z / MarchingCubesParams.ChunkSize.Z;
				
				int32 index = z * (MarchingCubesParams.ChunkSize.X + 1) * (MarchingCubesParams.ChunkSize.Y + 1) + y * (MarchingCubesParams.ChunkSize.X + 1) + x;
				densityMap[index] = MarchingCubesParams.SurfaceShapeGenerator->GetOutput3D(sampleX, sampleZ, sampleY);
				
				if (z == MarchingCubesParams.WaterLevel && densityMap[index] < MarchingCubesParams.SurfaceThreshold)
					hasWater = true;
			}
		}
	}

	FVoxelChunkData chunkData;
	chunkData.GridPosition = ChunkGridPosition;

	// Create water plane
	if (hasWater)
	{
		chunkData.WaterTriangles.Add(chunkData.WaterPositions.Num() + 0);
		chunkData.WaterTriangles.Add(chunkData.WaterPositions.Num() + 3);
		chunkData.WaterTriangles.Add(chunkData.WaterPositions.Num() + 2);
		chunkData.WaterTriangles.Add(chunkData.WaterPositions.Num() + 2);
		chunkData.WaterTriangles.Add(chunkData.WaterPositions.Num() + 1);
		chunkData.WaterTriangles.Add(chunkData.WaterPositions.Num() + 0);

		FVector v0 = { 0.0f,								   0.0f,								   (float)MarchingCubesParams.WaterLevel - 0.1f };
		FVector v1 = { (float)MarchingCubesParams.ChunkSize.X, 0.0f,								   (float)MarchingCubesParams.WaterLevel - 0.1f };
		FVector v2 = { (float)MarchingCubesParams.ChunkSize.X, (float)MarchingCubesParams.ChunkSize.Y, (float)MarchingCubesParams.WaterLevel - 0.1f };
		FVector v3 = { 0.0f,								   (float)MarchingCubesParams.ChunkSize.Y, (float)MarchingCubesParams.WaterLevel - 0.1f };
		chunkData.WaterPositions.Add(v0 * 100.0f);
		chunkData.WaterPositions.Add(v1 * 100.0f);
		chunkData.WaterPositions.Add(v2 * 100.0f);
		chunkData.WaterPositions.Add(v3 * 100.0f);

		FVector normal = { 0.0f, 0.0f, 1.0f };
		chunkData.WaterNormals.Add(normal);
		chunkData.WaterNormals.Add(normal);
		chunkData.WaterNormals.Add(normal);
		chunkData.WaterNormals.Add(normal);
		
		chunkData.WaterUVs.Add({ v0.X, v0.Y });
		chunkData.WaterUVs.Add({ v1.X, v1.Y });
		chunkData.WaterUVs.Add({ v2.X, v2.Y });
		chunkData.WaterUVs.Add({ v3.X, v3.Y });
	}

	// Create solid mesh using Marching cubes
	for (int32 z = 0; z < MarchingCubesParams.ChunkSize.Z; z++)
	{
		for (int32 y = 0; y < MarchingCubesParams.ChunkSize.Y; y++)
		{
			for (int32 x = 0; x < MarchingCubesParams.ChunkSize.X; x++)
			{
				float cubeCornerDensities[8];

				for (int32 i = 0; i < 8; i++)
				{
					FIntVector corner = { x + VertexOffsets[i][0], y + VertexOffsets[i][1], z + VertexOffsets[i][2]};

					int32 index = corner.Z * (MarchingCubesParams.ChunkSize.X + 1) * (MarchingCubesParams.ChunkSize.Y + 1) + corner.Y * (MarchingCubesParams.ChunkSize.X + 1) + corner.X;
					cubeCornerDensities[i] = densityMap[index];
				}

				MarchCube({ x, y, z }, cubeCornerDensities, MarchingCubesParams.SurfaceThreshold, MarchingCubesParams.InterpolateVertices, chunkData);
			}
		}
	}

	// Add the chunk to the queue
	OutputQueueLock.Lock();
	OutputQueue.Enqueue(MoveTemp(chunkData));
	OutputQueueLock.Unlock();
}

void FVoxelMeshGeneratorMC::MarchCube(const FIntVector& position, const float cubeCornerDensities[8], float surfaceThreshold, bool useInterpolation, FVoxelChunkData& outChunkData) const
{
	uint8 configIndex = 0;
	for (uint32 i = 0; i < 8; i++)
		if (cubeCornerDensities[i] >= surfaceThreshold)
			configIndex |= 1 << i;

	int32 usedEdgesMask = EdgeMasks[configIndex];
	if (usedEdgesMask == 0)
	{
		// We have no edges, nothing to add
		return;
	}

	FVector edgeVertices[12]; // A cube has 12 edges
	for (int32 i = 0; i < 12; i++)
	{
		if (EdgeMasks[configIndex] & (1 << i))
		{
			float interpolationFactor = useInterpolation ? GetInterpolationFactor(cubeCornerDensities[Edges[i][0]], cubeCornerDensities[Edges[i][1]], surfaceThreshold) : 0.5f;
			edgeVertices[i].X = position.X + (VertexOffsets[Edges[i][0]][0] + interpolationFactor * EdgeDirections[i][0]);
			edgeVertices[i].Y = position.Y + (VertexOffsets[Edges[i][0]][1] + interpolationFactor * EdgeDirections[i][1]);
			edgeVertices[i].Z = position.Z + (VertexOffsets[Edges[i][0]][2] + interpolationFactor * EdgeDirections[i][2]);
		}
	}

	// Add all triangles, we can have up to 5
	for (uint32 i = 0; i < 5; i++)
	{
		if (TriangleTable[configIndex][i * 3] == -1)
		{
			// No more triangles
			break;
		}

		// Add vertices and indices
		const FVector& v0 = edgeVertices[TriangleTable[configIndex][i * 3]];
		const FVector& v1 = edgeVertices[TriangleTable[configIndex][i * 3 + 1]];
		const FVector& v2 = edgeVertices[TriangleTable[configIndex][i * 3 + 2]];

		outChunkData.Triangles.Add(outChunkData.Positions.Num() + 0);
		outChunkData.Triangles.Add(outChunkData.Positions.Num() + 1);
		outChunkData.Triangles.Add(outChunkData.Positions.Num() + 2);

		// Convert to meters and add the vertices
		outChunkData.Positions.Add(v0 * 100);
		outChunkData.Positions.Add(v1 * 100);
		outChunkData.Positions.Add(v2 * 100);

		// Calculate normals
		FVector Normal = FVector::CrossProduct(v2 - v0, v1 - v0);
		Normal.Normalize();

		outChunkData.Normals.Add(Normal);
		outChunkData.Normals.Add(Normal);
		outChunkData.Normals.Add(Normal);

		// Calculate texture coordinates, use the normal vector to determine which plane we should project the UVs on
		Normal = { FMath::Abs(Normal.X), FMath::Abs(Normal.Y), FMath::Abs(Normal.Z) };

		if (Normal.X >= Normal.Z && Normal.X >= Normal.Y) // X plane
		{
			outChunkData.UVs.Add({ v0.Z, v0.Y });
			outChunkData.UVs.Add({ v1.Z, v1.Y });
			outChunkData.UVs.Add({ v2.Z, v2.Y });
		}
		else if (Normal.Z >= Normal.X && Normal.Z >= Normal.Y) // Z plane
		{
			outChunkData.UVs.Add({ v0.X, v0.Y });
			outChunkData.UVs.Add({ v1.X, v1.Y });
			outChunkData.UVs.Add({ v2.X, v2.Y });
		}
		else if (Normal.Y >= Normal.X && Normal.Y >= Normal.Z) // Y plane
		{
			outChunkData.UVs.Add({ v0.X, v0.Z });
			outChunkData.UVs.Add({ v1.X, v1.Z });
			outChunkData.UVs.Add({ v2.X, v2.Z });
		}
	}
}

float FVoxelMeshGeneratorMC::GetInterpolationFactor(float densityA, float densityB, float surfaceThreshold) const
{
	float range = densityB - densityA;
	return range == 0.0f ? 0.0f : (surfaceThreshold - densityA) / range;
}
