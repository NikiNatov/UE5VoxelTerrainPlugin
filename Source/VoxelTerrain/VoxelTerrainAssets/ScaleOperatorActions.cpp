#include "ScaleOperatorActions.h"
#include "../VoxelTerrainBuilder/ScaleOperator.h"

FScaleOperatorActions::FScaleOperatorActions(EAssetTypeCategories::Type category)
    : Category(category)
{
}

UClass* FScaleOperatorActions::GetSupportedClass() const
{
    return UScaleOperator::StaticClass();
}

FText FScaleOperatorActions::GetName() const
{
    return FText::FromString("Scale Operator");
}

FColor FScaleOperatorActions::GetTypeColor() const
{
    return FColor::Red;
}

uint32 FScaleOperatorActions::GetCategories()
{
    return Category;
}