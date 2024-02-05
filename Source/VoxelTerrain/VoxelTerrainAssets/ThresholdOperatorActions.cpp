#include "ThresholdOperatorActions.h"
#include "../VoxelTerrainBuilder/ThresholdOperator.h"

FThresholdOperatorActions::FThresholdOperatorActions(EAssetTypeCategories::Type category)
    : Category(category)
{
}

UClass* FThresholdOperatorActions::GetSupportedClass() const
{
    return UThresholdOperator::StaticClass();
}

FText FThresholdOperatorActions::GetName() const
{
    return FText::FromString("Threshold Operator");
}

FColor FThresholdOperatorActions::GetTypeColor() const
{
    return FColor::Red;
}

uint32 FThresholdOperatorActions::GetCategories()
{
    return Category;
}
