#include "ThresholdOperator.h"
#include "Math/UnrealMathUtility.h"

float UThresholdOperator::GetOutput2D(float x, float y)
{
    if (!IsValid(LowValueSource) || !IsValid(HighValueSource) || !IsValid(ControlValueSource))
        return 0.0f;

    float controlValue = ControlValueSource->GetOutput2D(x, y);
    float lowValue = LowValueSource->GetOutput2D(x, y);
    float highValue = HighValueSource->GetOutput2D(x, y);

    if (Falloff > 0.0f)
    {
        if (controlValue < Threshold - Falloff)
            return lowValue;
        else if (controlValue > Threshold + Falloff)
            return highValue;
        else
        {
            float lower = Threshold - Falloff;
            float upper = Threshold + Falloff;

            float f = (controlValue - lower) / (upper - lower);
            float blend = f * f * f * (f * (f * 6 - 15) + 10);
            return FMath::Lerp(lowValue, highValue, blend);
        }
    }
    
    if (controlValue >= Threshold)
        return highValue;

    return lowValue;
}

float UThresholdOperator::GetOutput3D(float x, float y, float z)
{
    if (!IsValid(LowValueSource) || !IsValid(HighValueSource) || !IsValid(ControlValueSource))
        return 0.0f;

    float controlValue = ControlValueSource->GetOutput3D(x, y, z);
    float lowValue = LowValueSource->GetOutput3D(x, y, z);
    float highValue = HighValueSource->GetOutput3D(x, y, z);

    if (Falloff > 0.0f)
    {
        if (controlValue < Threshold - Falloff)
            return lowValue;
        else if (controlValue > Threshold + Falloff)
            return highValue;
        else
        {
            float lower = Threshold - Falloff;
            float upper = Threshold + Falloff;

            float f = (controlValue - lower) / (upper - lower);
            float blend = f * f * f * (f * (f * 6 - 15) + 10);
            return FMath::Lerp(lowValue, highValue, blend);
        }
    }

    if (controlValue >= Threshold)
        return highValue;

    return lowValue;
}

void UThresholdOperator::SetTrasholdSource(float value)
{
    Threshold = value;
}

void UThresholdOperator::SetFalloff(float value)
{
    Falloff = value;
}

void UThresholdOperator::SetLowValueSource(UVoxelTerrainOperator* value)
{
    LowValueSource = value;
}

void UThresholdOperator::SetHighValueSource(UVoxelTerrainOperator* value)
{
    HighValueSource = value;
}

void UThresholdOperator::SetControlValueSource(UVoxelTerrainOperator* value)
{
    ControlValueSource = value;
}
