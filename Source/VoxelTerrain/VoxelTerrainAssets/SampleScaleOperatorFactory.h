#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "SampleScaleOperatorFactory.generated.h"

UCLASS()
class VOXELTERRAIN_API USampleScaleOperatorFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	USampleScaleOperatorFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
