#include "VoxelWorld.h"
#include "Math/UnrealMathUtility.h"
#include "FastNoiseWrapper.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Async/Async.h"

#include "VoxelTerrainBuilder/VoxelTerrainOperator.h"
#include "VoxelTerrainMeshGeneration/VoxelMeshGeneratorMC.h"


AVoxelWorld::AVoxelWorld()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AVoxelWorld::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(SurfaceShapeGenerator))
		return;

	CurrentChunkGridCoords = GetChunkGridCoordsAtPlayerPosition();

	// Generate chunks in a spiral around the player
	int32 x = 0;
	int32 y = 0;
	int32 dx = 0;
	int32 dy = -1;
	int32 gridSize = ChunkRenderDistance * 2 + 1;

	for (int32 i = 0; i < gridSize * gridSize; i++)
	{
		if ((x > -gridSize / 2 && x <= gridSize / 2) && (y > -gridSize / 2 && y <= gridSize / 2))
		{
			FIntVector2 chunkGridCoords = { CurrentChunkGridCoords.X + x, CurrentChunkGridCoords.Y + y };
			CreateChunkActor(chunkGridCoords);
			DispatchChunkGenerationTask(chunkGridCoords);
		}

		if (x == y || (x < 0 && x == -y) || (x > 0 && x == 1 - y))
		{
			int32 t = dx;
			dx = -dy;
			dy = t;
		}

		x = x + dx;
		y = y + dy;
	}
}

void AVoxelWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update chunks if player has moved into another chunk
	FIntVector2 playerChunkGridCoords = GetChunkGridCoordsAtPlayerPosition();
	if (CurrentChunkGridCoords != playerChunkGridCoords)
	{
		CurrentChunkGridCoords = playerChunkGridCoords;
		UpdateChunks();
	}

	// Process 1 chunk per frame
	ProcessPendingChunk();
}

void AVoxelWorld::UpdateChunks()
{
	FIntVector2 playerChunkGridCoords = GetChunkGridCoordsAtPlayerPosition();

	// Unload out of range chunks
	TArray<FIntVector2> chunksToUnload;
	for (auto& [gridCoords, chunk] : ActiveChunks)
	{
		if (gridCoords.X > playerChunkGridCoords.X + (int32)ChunkRenderDistance || gridCoords.X < playerChunkGridCoords.X - (int32)ChunkRenderDistance ||
			gridCoords.Y > playerChunkGridCoords.Y + (int32)ChunkRenderDistance || gridCoords.Y < playerChunkGridCoords.Y - (int32)ChunkRenderDistance)
		{
			chunksToUnload.Add(gridCoords);
		}
	}

	for (auto& gridCoords : chunksToUnload)
	{
		ActiveChunks[gridCoords]->Destroy();
		ActiveChunks.Remove(gridCoords);
	}

	// Load new chunks
	for (int32 i = -(int32)ChunkRenderDistance; i <= (int32)ChunkRenderDistance; i++)
	{
		for (int32 j = -(int32)ChunkRenderDistance; j <= (int32)ChunkRenderDistance; j++)
		{
			FIntVector2 chunkGridCoords = { playerChunkGridCoords.X + i, playerChunkGridCoords.Y + j };

			if (!ActiveChunks.Contains(chunkGridCoords))
			{
				CreateChunkActor(chunkGridCoords);
				DispatchChunkGenerationTask(chunkGridCoords);
			}
		}
	}
}

void AVoxelWorld::ProcessPendingChunk()
{
	if (PendingChunks.IsEmpty())
		return;

	FVoxelChunkData chunkData;
	PendingChunksLock.Lock();
	PendingChunks.Dequeue(chunkData);
	PendingChunksLock.Unlock();

	if (ActiveChunks.Contains(chunkData.GridPosition))
		ActiveChunks[chunkData.GridPosition]->UpdateMesh(chunkData, Material, WaterMaterial);
}

void AVoxelWorld::DispatchChunkGenerationTask(const FIntVector2& chunkGridPosition)
{
	AsyncTask(ENamedThreads::Type::AnyBackgroundThreadNormalTask, [chunkGridPosition, this]()
	{
		FMarchingCubesParams mcParams;
		mcParams.ChunkSize = { (int32)ChunkWidth, (int32)ChunkWidth, (int32)ChunkHeight };
		mcParams.WaterLevel = WaterLevel;
		mcParams.SurfaceThreshold = SurfaceThreshold;
		mcParams.InterpolateVertices = UseVertexInterpolation;
		mcParams.SurfaceShapeGenerator = SurfaceShapeGenerator;

		auto task = new FAsyncTask<FVoxelMeshGeneratorMC>(chunkGridPosition, mcParams, PendingChunks, PendingChunksLock);
		task->StartBackgroundTask();
		task->EnsureCompletion();
		delete task;
	});
}

void AVoxelWorld::CreateChunkActor(const FIntVector2& chunkGridPosition)
{
	FVector position = { (float)chunkGridPosition.X * (float)ChunkWidth, (float)chunkGridPosition.Y * (float)ChunkWidth, 0.0f };
	position *= 100.0f; // Convert to meters

	AVoxelChunk* Chunk = (AVoxelChunk*)(GetWorld()->SpawnActor(AVoxelChunk::StaticClass(), &position));
	Chunk->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	ActiveChunks.Add(chunkGridPosition, Chunk);
}

FIntVector2 AVoxelWorld::GetChunkGridCoordsAtPlayerPosition()
{
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	return GetChunkGridCoordsAtPosition(playerPosition / 100.0f);
}

FIntVector2 AVoxelWorld::GetChunkGridCoordsAtPosition(const FVector& worldPosition)
{
	return { FMath::FloorToInt32(worldPosition.X / (float)ChunkWidth), FMath::FloorToInt32(worldPosition.Y / (float)ChunkWidth) };
}
