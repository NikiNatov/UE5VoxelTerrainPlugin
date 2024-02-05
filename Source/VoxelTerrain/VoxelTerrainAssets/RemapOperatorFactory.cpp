#include "RemapOperatorFactory.h"
#include "../VoxelTerrainBuilder/RemapOperator.h"

URemapOperatorFactory::URemapOperatorFactory()
{
    SupportedClass = URemapOperator::StaticClass();
    bCreateNew = true;
}

UObject* URemapOperatorFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<URemapOperator>(InParent, Class, Name, Flags, Context);
}
