#include "SampleScaleOperatorFactory.h"
#include "../VoxelTerrainBuilder/SampleScaleOperator.h"

USampleScaleOperatorFactory::USampleScaleOperatorFactory()
{
    SupportedClass = USampleScaleOperator::StaticClass();
    bCreateNew = true;
}

UObject* USampleScaleOperatorFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<USampleScaleOperator>(InParent, Class, Name, Flags, Context);
}
