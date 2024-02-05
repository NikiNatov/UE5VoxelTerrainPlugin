#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ThresholdOperatorFactory.generated.h"

UCLASS()
class VOXELTERRAIN_API UThresholdOperatorFactory : public UFactory
{
	GENERATED_BODY()

public:
	UThresholdOperatorFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
