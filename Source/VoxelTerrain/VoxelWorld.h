// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelChunk.h"
#include "VoxelWorld.generated.h"

UCLASS()
class VOXELTERRAIN_API AVoxelWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	AVoxelWorld();

	virtual void Tick(float DeltaTime) override;

private:
	virtual void BeginPlay() override;

	void UpdateChunks();
	void ProcessPendingChunk();
	void DispatchChunkGenerationTask(const FIntVector2& chunkGridPosition);
	void CreateChunkActor(const FIntVector2& chunkGridPosition);

	FIntVector2 GetChunkGridCoordsAtPlayerPosition();
	FIntVector2 GetChunkGridCoordsAtPosition(const FVector& worldPosition);
private:
	UPROPERTY(EditAnywhere, Category = WorldSettings)
	uint32 ChunkRenderDistance = 6;

	UPROPERTY(EditAnywhere, Category = WorldSettings)
	uint32 ChunkWidth = 20;

	UPROPERTY(EditAnywhere, Category = WorldSettings)
	uint32 ChunkHeight = 100;

	UPROPERTY(EditAnywhere, Category = WorldSettings)
	uint32 WaterLevel = 20;

	UPROPERTY(EditAnywhere, Category = MarchingCubes)
	float SurfaceThreshold = 0.0f;

	UPROPERTY(EditAnywhere, Category = MarchingCubes)
	bool UseVertexInterpolation = true;

	UPROPERTY(EditAnywhere, Category = Materials)
	UMaterialInterface* Material = nullptr;

	UPROPERTY(EditAnywhere, Category = Materials)
	UMaterialInterface* WaterMaterial = nullptr;

	UPROPERTY(EditAnywhere, Category = TerrainGeneration)
	class UVoxelTerrainOperator* SurfaceShapeGenerator = nullptr;

	FIntVector2 CurrentChunkGridCoords;

	FCriticalSection PendingChunksLock;

	TQueue<FVoxelChunkData> PendingChunks;

	TMap<FIntVector2, class AVoxelChunk*> ActiveChunks;
};
