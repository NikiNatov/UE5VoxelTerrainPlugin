#include "OffsetOperatorFactory.h"
#include "../VoxelTerrainBuilder/OffsetOperator.h"

UOffsetOperatorFactory::UOffsetOperatorFactory()
{
    SupportedClass = UOffsetOperator::StaticClass();
    bCreateNew = true;
}

UObject* UOffsetOperatorFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<UOffsetOperator>(InParent, Class, Name, Flags, Context);
}