#include "VoxelTerrain.h"

#define LOCTEXT_NAMESPACE "FVoxelTerrainModule"

void FVoxelTerrainModule::StartupModule()
{
	// Register asset types
	IAssetTools& assetTools = FAssetToolsModule::GetModule().Get();
	EAssetTypeCategories::Type voxelOperatorsCategory = assetTools.RegisterAdvancedAssetCategory(FName(TEXT("VoxelTerrainOperators")), FText::FromString("Voxel Terrain Operators"));

	NoiseOperatorActions = MakeShared<FNoiseOperatorActions>(voxelOperatorsCategory);
	assetTools.RegisterAssetTypeActions(NoiseOperatorActions.ToSharedRef());

	ConstFloatOperatorActions = MakeShared<FConstFloatOperatorActions>(voxelOperatorsCategory);
	assetTools.RegisterAssetTypeActions(ConstFloatOperatorActions.ToSharedRef());

	ScaleOperatorActions = MakeShared<FScaleOperatorActions>(voxelOperatorsCategory);
	assetTools.RegisterAssetTypeActions(ScaleOperatorActions.ToSharedRef());

	OffsetOperatorActions = MakeShared<FOffsetOperatorActions>(voxelOperatorsCategory);
	assetTools.RegisterAssetTypeActions(OffsetOperatorActions.ToSharedRef());

	GradientOperatorActions = MakeShared<FGradientOperatorActions>(voxelOperatorsCategory);
	assetTools.RegisterAssetTypeActions(GradientOperatorActions.ToSharedRef());
	
	ThresholdOperatorActions = MakeShared<FThresholdOperatorActions>(voxelOperatorsCategory);
	assetTools.RegisterAssetTypeActions(ThresholdOperatorActions.ToSharedRef());
	
	RemapOperatorActions = MakeShared<FRemapOperatorActions>(voxelOperatorsCategory);
	assetTools.RegisterAssetTypeActions(RemapOperatorActions.ToSharedRef());
	
	SampleOffsetOperatorActions = MakeShared<FSampleOffsetOperatorActions>(voxelOperatorsCategory);
	assetTools.RegisterAssetTypeActions(SampleOffsetOperatorActions.ToSharedRef());
	
	SampleScaleOperatorActions = MakeShared<FSampleScaleOperatorActions>(voxelOperatorsCategory);
	assetTools.RegisterAssetTypeActions(SampleScaleOperatorActions.ToSharedRef());
}

void FVoxelTerrainModule::ShutdownModule()
{
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools"))
		return;

	// Unregister asset types
	IAssetTools& assetTools = FAssetToolsModule::GetModule().Get();

	assetTools.UnregisterAssetTypeActions(NoiseOperatorActions.ToSharedRef());
	assetTools.UnregisterAssetTypeActions(ConstFloatOperatorActions.ToSharedRef());
	assetTools.UnregisterAssetTypeActions(ScaleOperatorActions.ToSharedRef());
	assetTools.UnregisterAssetTypeActions(OffsetOperatorActions.ToSharedRef());
	assetTools.UnregisterAssetTypeActions(GradientOperatorActions.ToSharedRef());
	assetTools.UnregisterAssetTypeActions(ThresholdOperatorActions.ToSharedRef());
	assetTools.UnregisterAssetTypeActions(RemapOperatorActions.ToSharedRef());
	assetTools.UnregisterAssetTypeActions(SampleOffsetOperatorActions.ToSharedRef());
	assetTools.UnregisterAssetTypeActions(SampleScaleOperatorActions.ToSharedRef());

	assetTools.RegisterAdvancedAssetCategory(FName(TEXT("VoxelTerrainOperators")), FText::FromString("Voxel Terrain Operators"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVoxelTerrainModule, VoxelTerrain)