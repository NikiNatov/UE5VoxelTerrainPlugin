#pragma once

#include "CoreMinimal.h"
#include "VoxelTerrainOperator.h"
#include "RemapOperator.generated.h"

UCLASS(Blueprintable)
class VOXELTERRAIN_API URemapOperator : public UVoxelTerrainOperator
{
	GENERATED_BODY()

public:
	virtual float GetOutput2D(float x, float y) override;
	virtual float GetOutput3D(float x, float y, float z) override;

	void SetInputInterval(const FVector2D& value);
	void SetTargetInterval(const FVector2D& value);
	void SetInputSource(UVoxelTerrainOperator* value);
private:
	UPROPERTY(EditAnywhere)
	FVector2D InputInterval = { 0.0f, 1.0f };

	UPROPERTY(EditAnywhere)
	FVector2D TargetInterval = { 0.0f, 1.0f };

	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* InputSource = nullptr;
};
