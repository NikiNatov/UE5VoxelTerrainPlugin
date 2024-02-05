#include "SampleOffsetOperatorFactory.h"
#include "../VoxelTerrainBuilder/SampleOffsetOperator.h"

USampleOffsetOperatorFactory::USampleOffsetOperatorFactory()
{
    SupportedClass = USampleOffsetOperator::StaticClass();
    bCreateNew = true;
}

UObject* USampleOffsetOperatorFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<USampleOffsetOperator>(InParent, Class, Name, Flags, Context);
}
