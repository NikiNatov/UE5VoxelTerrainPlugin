#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "SampleOffsetOperatorFactory.generated.h"

UCLASS()
class VOXELTERRAIN_API USampleOffsetOperatorFactory : public UFactory
{
	GENERATED_BODY()

public:
	USampleOffsetOperatorFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
