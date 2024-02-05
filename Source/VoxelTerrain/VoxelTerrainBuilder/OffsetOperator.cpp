#include "OffsetOperator.h"

float UOffsetOperator::GetOutput2D(float x, float y)
{
    if (!IsValid(InputSource))
        return 0.0f;

    float offset = IsValid(OffsetSource) ? OffsetSource->GetOutput2D(x, y) : 0.0f;
    return InputSource->GetOutput2D(x, y) + offset;
}

float UOffsetOperator::GetOutput3D(float x, float y, float z)
{
    if (!IsValid(InputSource))
        return 0.0f;

    float offset = IsValid(OffsetSource) ? OffsetSource->GetOutput3D(x, y, z) : 0.0f;
    return InputSource->GetOutput3D(x, y, z) + offset;
}

void UOffsetOperator::SetOffsetSource(UVoxelTerrainOperator* value)
{
    OffsetSource = value;
}

void UOffsetOperator::SetInputSource(UVoxelTerrainOperator* value)
{
    InputSource = value;
}