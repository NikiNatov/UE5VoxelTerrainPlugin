#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "RemapOperatorFactory.generated.h"

UCLASS()
class VOXELTERRAIN_API URemapOperatorFactory : public UFactory
{
	GENERATED_BODY()
public:
	URemapOperatorFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
