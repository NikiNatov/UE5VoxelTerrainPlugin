#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ScaleOperatorFactory.generated.h"

UCLASS()
class VOXELTERRAIN_API UScaleOperatorFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	UScaleOperatorFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
