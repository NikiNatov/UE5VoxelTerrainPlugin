#include "ScaleOperatorFactory.h"
#include "../VoxelTerrainBuilder/ScaleOperator.h"

UScaleOperatorFactory::UScaleOperatorFactory()
{
    SupportedClass = UScaleOperator::StaticClass();
    bCreateNew = true;
}

UObject* UScaleOperatorFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<UScaleOperator>(InParent, Class, Name, Flags, Context);
}