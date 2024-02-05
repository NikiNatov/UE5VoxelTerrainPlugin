// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelChunk.generated.h"

struct FVoxelChunkData
{
	FIntVector2 GridPosition;

	TArray<FVector> Positions;
	TArray<FColor> Colors;
	TArray<FVector2D> UVs;
	TArray<FVector> Normals;
	TArray<int32> Triangles;

	TArray<FVector> WaterPositions;
	TArray<FVector2D> WaterUVs;
	TArray<FVector> WaterNormals;
	TArray<int32> WaterTriangles;
};

UCLASS()
class AVoxelChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	AVoxelChunk();

	virtual void Tick(float DeltaTime) override;

	void UpdateMesh(const FVoxelChunkData& updateData, UMaterialInterface* material, UMaterialInterface* waterMaterial);
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	class UProceduralMeshComponent* Mesh = nullptr;
};
