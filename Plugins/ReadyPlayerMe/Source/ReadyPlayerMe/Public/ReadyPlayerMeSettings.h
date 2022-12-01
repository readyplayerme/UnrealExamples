// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UObject/NoExportTypes.h"
#include "ReadyPlayerMeSettings.generated.h"

#if WITH_EDITOR
DECLARE_DELEGATE_OneParam(FEditorSettingsChanged, const FName&);
#endif

UCLASS(config=Game, defaultconfig, meta = (DisplayName="Ready Player Me"))
class READYPLAYERME_API UReadyPlayerMeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UReadyPlayerMeSettings();

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Avatar Caching", meta = (DisplayName = "Enable Avatar Caching",
		ToolTip = "If checked, the loaded avatars will be saved in the local storage."))
	bool bEnableAvatarCaching;

	static void SetAvatarCaching(bool bEnableCaching);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	FEditorSettingsChanged SettingsChanged;
#endif

};
