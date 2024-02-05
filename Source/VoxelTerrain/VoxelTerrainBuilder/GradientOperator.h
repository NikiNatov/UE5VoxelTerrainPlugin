#pragma once

#include "CoreMinimal.h"
#include "VoxelTerrainOperator.h"
#include "GradientOperator.generated.h"

UCLASS(Blueprintable)
class VOXELTERRAIN_API UGradientOperator : public UVoxelTerrainOperator
{
	GENERATED_BODY()

public:
	virtual float GetOutput2D(float x, float y) override;
	virtual float GetOutput3D(float x, float y, float z) override;

	void SetMinPoint(const FVector& value);
	void SetMaxPoint(const FVector& value);
private:
	UPROPERTY(EditAnywhere)
	FVector MinPoint = { 0.0f, 0.0f, 0.0f };

	UPROPERTY(EditAnywhere)
	FVector MaxPoint = { 1.0f, 1.0f, 1.0f };
};
