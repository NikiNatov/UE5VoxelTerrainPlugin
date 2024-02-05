#include "ConstFloatOperatorFactory.h"
#include "../VoxelTerrainBuilder/ConstFloatOperator.h"

UConstFloatOperatorFactory::UConstFloatOperatorFactory()
{
    SupportedClass = UConstFloatOperator::StaticClass();
    bCreateNew = true;
}

UObject* UConstFloatOperatorFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<UConstFloatOperator>(InParent, Class, Name, Flags, Context);
}