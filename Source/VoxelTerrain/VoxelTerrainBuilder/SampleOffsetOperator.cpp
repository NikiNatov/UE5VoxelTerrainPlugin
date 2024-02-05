#include "SampleOffsetOperator.h"

float USampleOffsetOperator::GetOutput2D(float x, float y)
{
    if (!IsValid(InputSource))
        return 0.0f;

    float xOffset = IsValid(XOffsetSource) ? XOffsetSource->GetOutput2D(x, y) : 0.0f;
    float yOffset = IsValid(YOffsetSource) ? YOffsetSource->GetOutput2D(x, y) : 0.0f;

    return InputSource->GetOutput2D(x + xOffset, y + yOffset);
}

float USampleOffsetOperator::GetOutput3D(float x, float y, float z)
{
    if (!IsValid(InputSource))
        return 0.0f;

    float xOffset = IsValid(XOffsetSource) ? XOffsetSource->GetOutput3D(x, y, z) : 0.0f;
    float yOffset = IsValid(YOffsetSource) ? YOffsetSource->GetOutput3D(x, y, z) : 0.0f;
    float zOffset = IsValid(ZOffsetSource) ? ZOffsetSource->GetOutput3D(x, y, z) : 0.0f;

    return InputSource->GetOutput3D(x + xOffset, y + yOffset, z + zOffset);
}

void USampleOffsetOperator::SetXOffsetSource(UVoxelTerrainOperator* value)
{
    XOffsetSource = value;
}

void USampleOffsetOperator::SetYOffsetSource(UVoxelTerrainOperator* value)
{
    YOffsetSource = value;
}

void USampleOffsetOperator::SetZOffsetSource(UVoxelTerrainOperator* value)
{
    ZOffsetSource = value;
}

void USampleOffsetOperator::SetInputSource(UVoxelTerrainOperator* value)
{
    InputSource = value;
}