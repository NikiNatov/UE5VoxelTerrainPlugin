#include "RemapOperatorActions.h"
#include "../VoxelTerrainBuilder/RemapOperator.h"

FRemapOperatorActions::FRemapOperatorActions(EAssetTypeCategories::Type category)
    : Category(category)
{
}

UClass* FRemapOperatorActions::GetSupportedClass() const
{
    return URemapOperator::StaticClass();
}

FText FRemapOperatorActions::GetName() const
{
    return FText::FromString("Remap Operator");
}

FColor FRemapOperatorActions::GetTypeColor() const
{
    return FColor::Red;
}

uint32 FRemapOperatorActions::GetCategories()
{
    return Category;
}