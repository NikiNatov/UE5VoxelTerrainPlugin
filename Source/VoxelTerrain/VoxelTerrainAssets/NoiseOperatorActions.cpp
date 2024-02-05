#include "NoiseOperatorActions.h"
#include "../VoxelTerrainBuilder/NoiseOperator.h"

FNoiseOperatorActions::FNoiseOperatorActions(EAssetTypeCategories::Type category)
    : Category(category)
{
}

UClass* FNoiseOperatorActions::GetSupportedClass() const
{
    return UNoiseOperator::StaticClass();
}

FText FNoiseOperatorActions::GetName() const
{
    return FText::FromString("Noise Operator");
}

FColor FNoiseOperatorActions::GetTypeColor() const
{
    return FColor::Red;
}

uint32 FNoiseOperatorActions::GetCategories()
{
    return Category;
}