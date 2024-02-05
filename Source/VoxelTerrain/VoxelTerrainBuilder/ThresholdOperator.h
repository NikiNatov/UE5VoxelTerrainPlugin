#pragma once

#include "CoreMinimal.h"
#include "VoxelTerrainOperator.h"
#include "ThresholdOperator.generated.h"

UCLASS(Blueprintable)
class VOXELTERRAIN_API UThresholdOperator : public UVoxelTerrainOperator
{
	GENERATED_BODY()

public:
	virtual float GetOutput2D(float x, float y) override;
	virtual float GetOutput3D(float x, float y, float z) override;

	void SetTrasholdSource(float value);
	void SetFalloff(float value);
	void SetLowValueSource(UVoxelTerrainOperator* value);
	void SetHighValueSource(UVoxelTerrainOperator* value);
	void SetControlValueSource(UVoxelTerrainOperator* value);
private:
	UPROPERTY(EditAnywhere)
	float Threshold = 0.5f;

	UPROPERTY(EditAnywhere)
	float Falloff = 0.0f;

	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* LowValueSource = nullptr;

	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* HighValueSource = nullptr;

	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* ControlValueSource = nullptr;
};