#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class VOXELTERRAIN_API FNoiseOperatorActions : public FAssetTypeActions_Base
{
public:
	FNoiseOperatorActions(EAssetTypeCategories::Type category);

	virtual UClass* GetSupportedClass() const override;
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type Category;
};
