#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ConstFloatOperatorFactory.generated.h"

UCLASS()
class VOXELTERRAIN_API UConstFloatOperatorFactory : public UFactory
{
	GENERATED_BODY()

public:
	UConstFloatOperatorFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
