#include "SampleOffsetOperatorActions.h"
#include "../VoxelTerrainBuilder/SampleOffsetOperator.h"

FSampleOffsetOperatorActions::FSampleOffsetOperatorActions(EAssetTypeCategories::Type category)
    : Category(category)
{
}

UClass* FSampleOffsetOperatorActions::GetSupportedClass() const
{
    return USampleOffsetOperator::StaticClass();
}

FText FSampleOffsetOperatorActions::GetName() const
{
    return FText::FromString("Sample Offset Operator");
}

FColor FSampleOffsetOperatorActions::GetTypeColor() const
{
    return FColor::Red;
}

uint32 FSampleOffsetOperatorActions::GetCategories()
{
    return Category;
}
