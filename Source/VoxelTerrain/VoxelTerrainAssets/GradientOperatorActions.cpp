#include "GradientOperatorActions.h"
#include "../VoxelTerrainBuilder/GradientOperator.h"

FGradientOperatorActions::FGradientOperatorActions(EAssetTypeCategories::Type category)
    : Category(category)
{
}

UClass* FGradientOperatorActions::GetSupportedClass() const
{
    return UGradientOperator::StaticClass();
}

FText FGradientOperatorActions::GetName() const
{
    return FText::FromString("Gradient Operator");
}

FColor FGradientOperatorActions::GetTypeColor() const
{
    return FColor::Red;
}

uint32 FGradientOperatorActions::GetCategories()
{
    return Category;
}
