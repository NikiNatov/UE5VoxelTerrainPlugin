#include "SampleScaleOperatorActions.h"
#include "../VoxelTerrainBuilder/SampleScaleOperator.h"

FSampleScaleOperatorActions::FSampleScaleOperatorActions(EAssetTypeCategories::Type category)
    : Category(category)
{
}

UClass* FSampleScaleOperatorActions::GetSupportedClass() const
{
    return USampleScaleOperator::StaticClass();
}

FText FSampleScaleOperatorActions::GetName() const
{
    return FText::FromString("Sample Scale Operator");
}

FColor FSampleScaleOperatorActions::GetTypeColor() const
{
    return FColor::Red;
}

uint32 FSampleScaleOperatorActions::GetCategories()
{
    return Category;
}
