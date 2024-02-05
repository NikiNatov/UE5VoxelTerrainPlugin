#include "SampleScaleOperator.h"

float USampleScaleOperator::GetOutput2D(float x, float y)
{
    if (!IsValid(InputSource))
        return 0.0f;

    float xScale = IsValid(XScaleSource) ? XScaleSource->GetOutput2D(x, y) : 1.0f;
    float yScale = IsValid(YScaleSource) ? YScaleSource->GetOutput2D(x, y) : 1.0f;

    return InputSource->GetOutput2D(x * xScale, y * yScale);
}

float USampleScaleOperator::GetOutput3D(float x, float y, float z)
{
    if (!IsValid(InputSource))
        return 0.0f;

    float xScale = IsValid(XScaleSource) ? XScaleSource->GetOutput3D(x, y, z) : 1.0f;
    float yScale = IsValid(YScaleSource) ? YScaleSource->GetOutput3D(x, y, z) : 1.0f;
    float zScale = IsValid(ZScaleSource) ? ZScaleSource->GetOutput3D(x, y, z) : 1.0f;

    return InputSource->GetOutput3D(x * xScale, y * yScale, z * zScale);
}

void USampleScaleOperator::SetXScaleSource(UVoxelTerrainOperator* value)
{
    XScaleSource = value;
}

void USampleScaleOperator::SetYScaleSource(UVoxelTerrainOperator* value)
{
    YScaleSource = value;
}

void USampleScaleOperator::SetZScaleSource(UVoxelTerrainOperator* value)
{
    ZScaleSource = value;
}

void USampleScaleOperator::SetInputSource(UVoxelTerrainOperator* value)
{
    InputSource = value;
}