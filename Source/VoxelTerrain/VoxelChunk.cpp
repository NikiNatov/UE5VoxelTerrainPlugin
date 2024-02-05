#include "VoxelChunk.h"
#include "ProceduralMeshComponent.h"
#include "VoxelWorld.h"

AVoxelChunk::AVoxelChunk()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("VoxelChunkMesh"));
	Mesh->SetupAttachment(GetRootComponent());
}

void AVoxelChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVoxelChunk::UpdateMesh(const FVoxelChunkData& updateData, UMaterialInterface* material, UMaterialInterface* waterMaterial)
{
	Mesh->CreateMeshSection(0, updateData.Positions, updateData.Triangles, updateData.Normals, updateData.UVs, updateData.Colors, TArray<FProcMeshTangent>(), true);
	Mesh->SetMaterial(0, material);
	Mesh->CreateMeshSection(1, updateData.WaterPositions, updateData.WaterTriangles, updateData.WaterNormals, updateData.WaterUVs, TArray<FColor>(), TArray<FProcMeshTangent>(), false);
	Mesh->SetMaterial(1, waterMaterial);
	Mesh->SetCastShadow(false);
}

void AVoxelChunk::BeginPlay()
{
	Super::BeginPlay();
}
