#pragma once

#include "CoreMinimal.h"
#include "VoxelTerrainOperator.h"
#include "OffsetOperator.generated.h"

UCLASS(Blueprintable)
class VOXELTERRAIN_API UOffsetOperator : public UVoxelTerrainOperator
{
	GENERATED_BODY()
	
public:
	virtual float GetOutput2D(float x, float y) override;
	virtual float GetOutput3D(float x, float y, float z) override;

	void SetOffsetSource(UVoxelTerrainOperator* value);
	void SetInputSource(UVoxelTerrainOperator* value);
private:
	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* OffsetSource = nullptr;

	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* InputSource = nullptr;
};
