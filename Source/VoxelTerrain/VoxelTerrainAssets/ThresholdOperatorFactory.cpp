#include "ThresholdOperatorFactory.h"
#include "../VoxelTerrainBuilder/ThresholdOperator.h"

UThresholdOperatorFactory::UThresholdOperatorFactory()
{
    SupportedClass = UThresholdOperator::StaticClass();
    bCreateNew = true;
}

UObject* UThresholdOperatorFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<UThresholdOperator>(InParent, Class, Name, Flags, Context);
}