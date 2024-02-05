#include "NoiseOperatorFactory.h"
#include "../VoxelTerrainBuilder/NoiseOperator.h"

UNoiseOperatorFactory::UNoiseOperatorFactory()
{
    SupportedClass = UNoiseOperator::StaticClass();
    bCreateNew = true;
}

UObject* UNoiseOperatorFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<UNoiseOperator>(InParent, Class, Name, Flags, Context);
}