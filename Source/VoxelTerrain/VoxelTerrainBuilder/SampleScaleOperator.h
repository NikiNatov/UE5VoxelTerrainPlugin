#pragma once

#include "CoreMinimal.h"
#include "VoxelTerrainOperator.h"
#include "SampleScaleOperator.generated.h"

UCLASS(Blueprintable)
class VOXELTERRAIN_API USampleScaleOperator : public UVoxelTerrainOperator
{
	GENERATED_BODY()
	
public:
	virtual float GetOutput2D(float x, float y) override;
	virtual float GetOutput3D(float x, float y, float z) override;

	void SetXScaleSource(UVoxelTerrainOperator* value);
	void SetYScaleSource(UVoxelTerrainOperator* value);
	void SetZScaleSource(UVoxelTerrainOperator* value);
	void SetInputSource(UVoxelTerrainOperator* value);
private:
	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* XScaleSource = nullptr;

	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* YScaleSource = nullptr;

	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* ZScaleSource = nullptr;

	UPROPERTY(EditAnywhere)
	UVoxelTerrainOperator* InputSource = nullptr;
};
