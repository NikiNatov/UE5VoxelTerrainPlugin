#include "VoxelTerrainOperator.h"

UVoxelTerrainOperator::UVoxelTerrainOperator()
{
}

#if WITH_EDITORONLY_DATA
void UVoxelTerrainOperator::PostLoad()
{
    Super::PostLoad();
    GeneratePreviewTexture();
}

void UVoxelTerrainOperator::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
    FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
    if (PropertyName == GET_MEMBER_NAME_CHECKED(UVoxelTerrainOperator, PreviewTexture))
    {
        Super::PostEditChangeProperty(e);
        return;
    }

    GeneratePreviewTexture();

    Super::PostEditChangeProperty(e);
}

void UVoxelTerrainOperator::GeneratePreviewTexture()
{
    if (!IsValid(PreviewTexture))
    {
        PreviewTexture = UTexture2D::CreateTransient(PreviewImageSize, PreviewImageSize, PF_B8G8R8A8);
        PreviewTexture->MipGenSettings = TMGS_NoMipmaps;
    }

    TArray<FColor> previewTextureData;
    previewTextureData.SetNumZeroed(PreviewImageSize * PreviewImageSize);

    for (int32 y = 0; y < PreviewImageSize; y++)
    {
        for (int32 x = 0; x < PreviewImageSize; x++)
        {
            float value = FMath::Clamp(GetOutput2D((float)x / PreviewImageSize, (float)y / PreviewImageSize), 0.0f, 1.0f);
            previewTextureData[(PreviewImageSize - 1 - y) * PreviewImageSize + x].R = value * 255;
            previewTextureData[(PreviewImageSize - 1 - y) * PreviewImageSize + x].G = value * 255;
            previewTextureData[(PreviewImageSize - 1 - y) * PreviewImageSize + x].B = value * 255;
            previewTextureData[(PreviewImageSize - 1 - y) * PreviewImageSize + x].A = 255;
        }
    }

    void* textureData = PreviewTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
    int32 previewDataSize = previewTextureData.Num() * 4;
    FMemory::Memcpy(textureData, previewTextureData.GetData(), previewDataSize);
    PreviewTexture->PlatformData->Mips[0].BulkData.Unlock();
    PreviewTexture->UpdateResource();
}
#endif // #if WITH_EDITORONLY_DATA
