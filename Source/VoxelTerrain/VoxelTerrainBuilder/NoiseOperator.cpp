#include "NoiseOperator.h"

UNoiseOperator::UNoiseOperator()
{
    NoiseGenerator = CreateDefaultSubobject<UFastNoiseWrapper>(TEXT("NoiseGenerator"));
}

float UNoiseOperator::GetOutput2D(float x, float y)
{
    return FMath::Pow(NoiseGenerator->GetNoise2D(x, y) * 0.5f + 0.5f, Exponent);
}

float UNoiseOperator::GetOutput3D(float x, float y, float z)
{
    return FMath::Pow(NoiseGenerator->GetNoise3D(x, y, z) * 0.5f + 0.5f, Exponent);
}

void UNoiseOperator::SetSeed(uint64 value)
{
    Seed = value;
    NoiseGenerator->SetupFastNoise(NoiseType, Seed, Frequency, InterpolationType, FractalType, Octaves, Lacunarity, Persistence);
}

void UNoiseOperator::SetNoiseType(EFastNoise_NoiseType value)
{
    NoiseType = value;
    NoiseGenerator->SetupFastNoise(NoiseType, Seed, Frequency, InterpolationType, FractalType, Octaves, Lacunarity, Persistence);
}

void UNoiseOperator::SetInterpolationType(EFastNoise_Interp value)
{
    InterpolationType = value;
    NoiseGenerator->SetupFastNoise(NoiseType, Seed, Frequency, InterpolationType, FractalType, Octaves, Lacunarity, Persistence);
}

void UNoiseOperator::SetFractalType(EFastNoise_FractalType value)
{
    FractalType = value;
    NoiseGenerator->SetupFastNoise(NoiseType, Seed, Frequency, InterpolationType, FractalType, Octaves, Lacunarity, Persistence);
}

void UNoiseOperator::SetOctaves(uint8 value)
{
    if (value >= MinOctaves && value <= MaxOctaves)
    {
        Octaves = value;
        NoiseGenerator->SetupFastNoise(NoiseType, Seed, Frequency, InterpolationType, FractalType, Octaves, Lacunarity, Persistence);
    }
}

void UNoiseOperator::SetFrequency(float value)
{
    Frequency = value;
    NoiseGenerator->SetupFastNoise(NoiseType, Seed, Frequency, InterpolationType, FractalType, Octaves, Lacunarity, Persistence);
}

void UNoiseOperator::SetLacunarity(float value)
{
    Lacunarity = value;
    NoiseGenerator->SetupFastNoise(NoiseType, Seed, Frequency, InterpolationType, FractalType, Octaves, Lacunarity, Persistence);
}

void UNoiseOperator::SetPersistence(float value)
{
    Persistence = value;
    NoiseGenerator->SetupFastNoise(NoiseType, Seed, Frequency, InterpolationType, FractalType, Octaves, Lacunarity, Persistence);
}

void UNoiseOperator::PostLoad()
{
    Super::PostLoad();
    NoiseGenerator->SetupFastNoise(NoiseType, Seed, Frequency, InterpolationType, FractalType, Octaves, Lacunarity, Persistence);
}

void UNoiseOperator::PostEditChangeProperty(FPropertyChangedEvent& e)
{
    NoiseGenerator->SetupFastNoise(NoiseType, Seed, Frequency, InterpolationType, FractalType, Octaves, Lacunarity, Persistence);
    Super::PostEditChangeProperty(e);
}
