#pragma once

#include "CoreMinimal.h"
#include "VoxelTerrainOperator.h"
#include "ConstFloatOperator.generated.h"

UCLASS(Blueprintable)
class VOXELTERRAIN_API UConstFloatOperator : public UVoxelTerrainOperator
{
	GENERATED_BODY()
	
public:
	virtual float GetOutput2D(float x, float y) override;
	virtual float GetOutput3D(float x, float y, float z) override;

	void SetValue(float value);
private:
	UPROPERTY(EditAnywhere)
	float Value = 0.0f;
};
