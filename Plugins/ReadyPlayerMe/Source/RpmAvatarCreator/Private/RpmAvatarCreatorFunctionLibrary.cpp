// Copyright © 2023++ Ready Player Me

#include "RpmAvatarCreatorFunctionLibrary.h"
#include "Serialization/BufferArchive.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Misc/Base64.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Components/SkeletalMeshComponent.h"
#include "ImageUtils.h"
#include "Requests/Endpoints.h"

FString URpmAvatarCreatorFunctionLibrary::GetBase64String(UTextureRenderTarget2D* TextureRenderTarget)
{
    FBufferArchive Buffer;
    if (FImageUtils::ExportRenderTarget2DAsPNG(TextureRenderTarget, Buffer))
    {
        return FBase64::Encode(const_cast<uint8*>(Buffer.GetData()), Buffer.Num());
    }
    return {};
}

FString URpmAvatarCreatorFunctionLibrary::GetAvatarUrl(const FString& AvatarId)
{
    return FEndpoints::GetAvatarPublicUrl(AvatarId);
}

USkeletalMesh* URpmAvatarCreatorFunctionLibrary::GetSkeletalMeshFromComponent(const USkeletalMeshComponent* Component)
{
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION > 0
    return Component->GetSkeletalMeshAsset();
#else
    return Component->SkeletalMesh;
#endif
}
