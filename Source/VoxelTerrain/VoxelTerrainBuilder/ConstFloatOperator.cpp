#include "ConstFloatOperator.h"

float UConstFloatOperator::GetOutput2D(float x, float y)
{
    return Value;
}

float UConstFloatOperator::GetOutput3D(float x, float y, float z)
{
    return Value;
}

void UConstFloatOperator::SetValue(float value)
{
    Value = value;
}