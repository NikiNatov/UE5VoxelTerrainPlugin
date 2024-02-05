#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "VoxelTerrainAssets/NoiseOperatorActions.h"
#include "VoxelTerrainAssets/ConstFloatOperatorActions.h"
#include "VoxelTerrainAssets/ScaleOperatorActions.h"
#include "VoxelTerrainAssets/OffsetOperatorActions.h"
#include "VoxelTerrainAssets/GradientOperatorActions.h"
#include "VoxelTerrainAssets/ThresholdOperatorActions.h"
#include "VoxelTerrainAssets/RemapOperatorActions.h"
#include "VoxelTerrainAssets/SampleOffsetOperatorActions.h"
#include "VoxelTerrainAssets/SampleScaleOperatorActions.h"

class FVoxelTerrainModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<FNoiseOperatorActions> NoiseOperatorActions;
	TSharedPtr<FConstFloatOperatorActions> ConstFloatOperatorActions;
	TSharedPtr<FScaleOperatorActions> ScaleOperatorActions;
	TSharedPtr<FOffsetOperatorActions> OffsetOperatorActions;
	TSharedPtr<FGradientOperatorActions> GradientOperatorActions;
	TSharedPtr<FThresholdOperatorActions> ThresholdOperatorActions;
	TSharedPtr<FRemapOperatorActions> RemapOperatorActions;
	TSharedPtr<FSampleOffsetOperatorActions> SampleOffsetOperatorActions;
	TSharedPtr<FSampleScaleOperatorActions> SampleScaleOperatorActions;
};
