#include "OffsetOperatorActions.h"
#include "../VoxelTerrainBuilder/OffsetOperator.h"

FOffsetOperatorActions::FOffsetOperatorActions(EAssetTypeCategories::Type category)
    : Category(category)
{
}

UClass* FOffsetOperatorActions::GetSupportedClass() const
{
    return UOffsetOperator::StaticClass();
}

FText FOffsetOperatorActions::GetName() const
{
    return FText::FromString("Offset Operator");
}

FColor FOffsetOperatorActions::GetTypeColor() const
{
    return FColor::Red;
}

uint32 FOffsetOperatorActions::GetCategories()
{
    return Category;
}
