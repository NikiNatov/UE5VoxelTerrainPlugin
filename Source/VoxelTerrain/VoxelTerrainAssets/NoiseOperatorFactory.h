#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "NoiseOperatorFactory.generated.h"

UCLASS()
class VOXELTERRAIN_API UNoiseOperatorFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	UNoiseOperatorFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
