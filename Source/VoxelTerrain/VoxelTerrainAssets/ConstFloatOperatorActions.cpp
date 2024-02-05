#include "ConstFloatOperatorActions.h"
#include "../VoxelTerrainBuilder/ConstFloatOperator.h"

FConstFloatOperatorActions::FConstFloatOperatorActions(EAssetTypeCategories::Type category)
    : Category(category)
{
}

UClass* FConstFloatOperatorActions::GetSupportedClass() const
{
    return UConstFloatOperator::StaticClass();
}

FText FConstFloatOperatorActions::GetName() const
{
    return FText::FromString("Const Float Operator");
}

FColor FConstFloatOperatorActions::GetTypeColor() const
{
    return FColor::Red;
}

uint32 FConstFloatOperatorActions::GetCategories()
{
    return Category;
}
