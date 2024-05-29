// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UObject/NoExportTypes.h"
#include "ReadyPlayerMeSettings.generated.h"

#if WITH_EDITOR
DECLARE_DELEGATE_OneParam(FEditorSettingsChanged, const FName&);
#endif

USTRUCT()
struct READYPLAYERME_API FRpmAvatarCacheSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Avatar Caching", meta = (DisplayName = "Enable Avatar Caching",
	ToolTip = "If checked, the loaded avatars will be saved in the local storage."))
	bool bEnableAvatarCaching = false;

	UPROPERTY(EditAnywhere, Category = "Avatar Caching | Automated Cleanup", meta = (DisplayName = "Enable Automatic Avatar Cache Cleaning",
		ToolTip = "If checked, the old avatars will be automatically removed if the number of the saved avatars exceeds the cached avatar limit."))
	bool bEnableAutomaticCacheCleaning = false;

	UPROPERTY(EditAnywhere, Category = "Avatar Caching | Automated Cleanup", meta = (DisplayName = "Cached Avatar Limit",
				ToolTip = "The limit of the cached avatars, when the limit is exceeded and the automatic cleaning is enabled the old avatars will automatically be cleaned."))
	int32 CachedAvatarLimit = 30;
};

UCLASS(config=Game, defaultconfig, meta = (DisplayName="Ready Player Me"))
class READYPLAYERME_API UReadyPlayerMeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UReadyPlayerMeSettings();

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "App ID",
	ToolTip = "The App ID is used to identify your application. You can find it in the Ready Player Me application dashboard in studio https://studio.readyplayer.me/applications."))
	FString AppId;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Subdomain",
	ToolTip = "The Subdomain is used to identify your application. You can find it in the Ready Player Me application dashboard in studio https://studio.readyplayer.me/applications."))
	FString Subdomain;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Keep Loaded Avatars In Memory",
		ToolTip = "If checked, the loaded avatars will be kept in the memory and will be reused afterwards."))
	bool bKeepLoadedAvatarsInMemory;

	UPROPERTY(Config, EditAnywhere, Category = "Settings", meta = (DisplayName = "Avatar Cache Settings",
	ToolTip = "Settings for saving the avatars in the local storage."))
	FRpmAvatarCacheSettings AvatarCacheSettings;

	static void SetAvatarCaching(bool bEnableCaching);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	FEditorSettingsChanged SettingsChanged;
#endif

};
