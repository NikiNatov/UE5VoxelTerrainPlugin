#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "GradientOperatorFactory.generated.h"

UCLASS()
class VOXELTERRAIN_API UGradientOperatorFactory : public UFactory
{
	GENERATED_BODY()

public:
	UGradientOperatorFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
