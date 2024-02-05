#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VoxelTerrainOperator.generated.h"

UCLASS(Abstract)
class VOXELTERRAIN_API UVoxelTerrainOperator : public UObject
{
	GENERATED_BODY()

public:
	UVoxelTerrainOperator();

	virtual float GetOutput2D(float x, float y) PURE_VIRTUAL(UTerrainGraphNode::GetOutput2D, return 0.0f;);
	virtual float GetOutput3D(float x, float y, float z) PURE_VIRTUAL(UTerrainGraphNode::GetOutput3D, return 0.0f;);

#if WITH_EDITORONLY_DATA
protected:
	static constexpr uint32 PreviewImageSize = 128;

	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
	void GeneratePreviewTexture();
protected:
	UPROPERTY(VisibleAnywhere, Transient, Category = Preview)
	UTexture2D* PreviewTexture = nullptr;
#endif
};
