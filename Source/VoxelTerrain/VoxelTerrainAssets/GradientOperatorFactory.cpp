#include "GradientOperatorFactory.h"
#include "../VoxelTerrainBuilder/GradientOperator.h"

UGradientOperatorFactory::UGradientOperatorFactory()
{
    SupportedClass = UGradientOperator::StaticClass();
    bCreateNew = true;
}

UObject* UGradientOperatorFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<UGradientOperator>(InParent, Class, Name, Flags, Context);
}
