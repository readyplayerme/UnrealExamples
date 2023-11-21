// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RpmAvatarCreatorFunctionLibrary.generated.h"

/**
 * Static functions to be used from the blueprint.
 */
UCLASS()
class RPMAVATARCREATOR_API URpmAvatarCreatorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Get the Base64 string of the image in the Render Target. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Get Base64 String From Render Target"))
	static FString GetBase64String(class UTextureRenderTarget2D* TextureRenderTarget);

	/** Get avatar Url from avatar id. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Get Avatar Url From Avatar Id"))
	static FString GetAvatarUrl(const FString& AvatarId);

	/** Get skeletal mesh from the skeletal mesh component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ready Player Me", meta = (DisplayName = "Get Skeletal Mesh From Component"))
	static class USkeletalMesh* GetSkeletalMeshFromComponent(const class USkeletalMeshComponent* Component);
};
