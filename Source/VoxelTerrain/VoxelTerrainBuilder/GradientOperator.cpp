#include "GradientOperator.h"

float UGradientOperator::GetOutput2D(float x, float y)
{
    // Form a gradient image by projecting the input point (x, y) on the segment formed by MinPoint and MaxPoint
    // If the projects before or on MinPoint we get a value of 0.0
    // If the projects after or on MaxPoint we get a value of 1.0
    // The values in the middle get linearly interpolated

    FVector2D minPoint2D = { MinPoint.X, MinPoint.Y };
    FVector2D maxPoint2D = { MaxPoint.X, MaxPoint.Y };

    FVector2D segmentDirection = maxPoint2D - minPoint2D;
    FVector2D inputDirection = FVector2D(x, y) - minPoint2D;

    float segmentLength = segmentDirection.Length();
    segmentDirection.Normalize();

    // Project the point and find where on the segment it lies
    float factor = FVector2D::DotProduct(segmentDirection, inputDirection);

    // Normalize and clamp the value between 0.0 and 1.0
    return FMath::Clamp(factor / segmentLength, 0.0f, 1.0f);
}

float UGradientOperator::GetOutput3D(float x, float y, float z)
{
    // Form a gradient image by projecting the input point (x, y, z) on the segment formed by MinPoint and MaxPoint
    // If the projects before or on MinPoint we get a value of 0.0
    // If the projects after or on MaxPoint we get a value of 1.0
    // The values in the middle get linearly interpolated

    FVector segmentDirection = MaxPoint - MinPoint;
    FVector inputDirection = FVector(x, y, z) - MinPoint;

    float segmentLength = segmentDirection.Length();
    segmentDirection.Normalize();

    // Project the point and find where on the segment it lies
    float factor = FVector::DotProduct(segmentDirection, inputDirection);

    // Normalize and clamp the value between 0.0 and 1.0
    return FMath::Clamp(factor / segmentLength, 0.0f, 1.0f);
}

void UGradientOperator::SetMinPoint(const FVector& value)
{
    MinPoint = value;
}

void UGradientOperator::SetMaxPoint(const FVector& value)
{
    MaxPoint = value;
}