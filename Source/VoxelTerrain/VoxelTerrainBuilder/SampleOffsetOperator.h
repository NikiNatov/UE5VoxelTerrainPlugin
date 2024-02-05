#pragma once

#include "CoreMinimal.h"
#include "VoxelTerrainOperator.h"
#include "SampleOffsetOperator.generated.h"

UCLASS(Blueprintable)
class VOXELTERRAIN_API USampleOffsetOperator : public UVoxelTerrainOperator
{
	GENERATED_BODY()
	
public:
	virtual float GetOutput2D(float x, float y) override;
	virtual float GetOutput3D(float x, float y, float z) override;

	void SetXOffsetSource(UVoxelTerrainOperator* value);
	void SetYOffsetSource(UVoxelTerrainOperator* value);
	void SetZOffsetSource(UVoxelTerrainOperator* value);
	void SetInputSource(UVoxelTerrainOperator* value);
private:
	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* XOffsetSource = nullptr;

	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* YOffsetSource = nullptr;

	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* ZOffsetSource = nullptr;

	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* InputSource = nullptr;
};
