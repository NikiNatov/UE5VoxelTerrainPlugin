#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "OffsetOperatorFactory.generated.h"

UCLASS()
class VOXELTERRAIN_API UOffsetOperatorFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	UOffsetOperatorFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
