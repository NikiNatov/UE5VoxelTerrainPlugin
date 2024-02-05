#include "ScaleOperator.h"

float UScaleOperator::GetOutput2D(float x, float y)
{
    if (!IsValid(InputSource))
        return 0.0f;

    float scale = IsValid(ScaleSource) ? ScaleSource->GetOutput2D(x, y) : 1.0f;
    return InputSource->GetOutput2D(x, y) * scale;
}

float UScaleOperator::GetOutput3D(float x, float y, float z)
{
    if (!IsValid(InputSource))
        return 0.0f;

    float scale = IsValid(ScaleSource) ? ScaleSource->GetOutput3D(x, y, z) : 1.0f;
    return InputSource->GetOutput3D(x, y, z) * scale;
}

void UScaleOperator::SetScaleSource(UVoxelTerrainOperator* value)
{
    ScaleSource = value;
}

void UScaleOperator::SetInputSource(UVoxelTerrainOperator* value)
{
    InputSource = value;
}