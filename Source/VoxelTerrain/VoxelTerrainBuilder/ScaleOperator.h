#pragma once

#include "CoreMinimal.h"
#include "VoxelTerrainOperator.h"
#include "ScaleOperator.generated.h"

UCLASS(Blueprintable)
class VOXELTERRAIN_API UScaleOperator : public UVoxelTerrainOperator
{
	GENERATED_BODY()

public:
	virtual float GetOutput2D(float x, float y) override;
	virtual float GetOutput3D(float x, float y, float z) override;

	void SetScaleSource(UVoxelTerrainOperator* value);
	void SetInputSource(UVoxelTerrainOperator* value);
private:
	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* ScaleSource = nullptr;

	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* InputSource = nullptr;
};
