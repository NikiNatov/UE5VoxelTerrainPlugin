#include "RemapOperator.h"

float URemapOperator::GetOutput2D(float x, float y)
{
    if (!IsValid(InputSource))
        return 0.0f;

    if (InputInterval.Y - InputInterval.X == 0.0f)
        return 0.0f;

    float value = InputSource->GetOutput2D(x, y);
    return TargetInterval.X + (value - InputInterval.X) * (TargetInterval.Y - TargetInterval.X) / (InputInterval.Y - InputInterval.X);
}

float URemapOperator::GetOutput3D(float x, float y, float z)
{
    if (!IsValid(InputSource))
        return 0.0f;

    if (InputInterval.Y - InputInterval.X == 0.0f)
        return 0.0f;

    float value = InputSource->GetOutput3D(x, y, z);
    return TargetInterval.X + (value - InputInterval.X) * (TargetInterval.Y - TargetInterval.X) / (InputInterval.Y - InputInterval.X);
}

void URemapOperator::SetInputInterval(const FVector2D& value)
{
    InputInterval = value;
}

void URemapOperator::SetTargetInterval(const FVector2D& value)
{
    TargetInterval = value;
}

void URemapOperator::SetInputSource(UVoxelTerrainOperator* value)
{
    InputSource = value;
}