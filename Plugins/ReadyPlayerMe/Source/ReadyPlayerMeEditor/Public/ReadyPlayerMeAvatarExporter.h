// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"
#include "ReadyPlayerMeAvatarExporter.generated.h"

/**
 * Used to export Mixamo compatible FBX files from the avatar url.
 */
UCLASS(BlueprintType)
class READYPLAYERMEEDITOR_API UReadyPlayerMeAvatarExporter : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UReadyPlayerMeAvatarExporter();

	/**
	 * Exports the FBX file and shows a dialog for choosing the location.
	 * 
	 * @param Url avatar url.
	 */
	UFUNCTION(BlueprintCallable, Category = "Asset Tools")
	void ExportAvatarWithDialog(const FString& Url);

private:
	UPROPERTY()
	class UReadyPlayerMeAvatarLoader* AvatarLoader;

	UFUNCTION()
	void OnAvatarDownloaded(class UglTFRuntimeAsset* Asset, const FAvatarMetadata& Metadata);

	UFUNCTION()
	void OnAvatarDownloadFailed(const FString& ErrorMessage);

	FAvatarDownloadCompleted OnAvatarDownloadCompleted;
	FAvatarLoadFailed OnLoadFailed;
};
