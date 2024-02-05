#pragma once

#include "CoreMinimal.h"
#include "VoxelTerrainOperator.h"
#include "FastNoiseWrapper.h"
#include "NoiseOperator.generated.h"

UCLASS(Blueprintable)
class VOXELTERRAIN_API UNoiseOperator : public UVoxelTerrainOperator
{
	GENERATED_BODY()
public:
	UNoiseOperator();

	virtual float GetOutput2D(float x, float y) override;
	virtual float GetOutput3D(float x, float y, float z) override;

	void SetSeed(uint64 value);
	void SetNoiseType(EFastNoise_NoiseType value);
	void SetInterpolationType(EFastNoise_Interp value);
	void SetFractalType(EFastNoise_FractalType value);
	void SetOctaves(uint8 value);
	void SetFrequency(float value);
	void SetLacunarity(float value);
	void SetPersistence(float value);

private:
	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
private:
	static constexpr uint8 MinOctaves = 1;
	static constexpr uint8 MaxOctaves = 10;

private:
	UPROPERTY(EditAnywhere)
	uint64 Seed = 0;

	UPROPERTY(EditAnywhere)
	EFastNoise_NoiseType NoiseType = EFastNoise_NoiseType::SimplexFractal;

	UPROPERTY(EditAnywhere)
	EFastNoise_Interp InterpolationType = EFastNoise_Interp::Quintic;

	UPROPERTY(EditAnywhere)
	EFastNoise_FractalType FractalType = EFastNoise_FractalType::FBM;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = "1", ClampMax = "10", UIMin = "1", UIMax = "10"))
	uint8 Octaves = 1;

	UPROPERTY(EditAnywhere)
	float Frequency = 0.01f;

	UPROPERTY(EditAnywhere)
	float Lacunarity = 2.0f;

	UPROPERTY(EditAnywhere)
	float Persistence = 0.5f;

	UPROPERTY(EditAnywhere)
	float Exponent = 1.0f;

	UPROPERTY()
	UFastNoiseWrapper* NoiseGenerator = nullptr;
};
