// Copyright © 2024 Ready Player Me

#include "ReadyPlayerMeSettings.h"

UReadyPlayerMeSettings::UReadyPlayerMeSettings()
	: bKeepLoadedAvatarsInMemory(false)
{
}

void UReadyPlayerMeSettings::SetAvatarCaching(bool bEnableCaching)
{
	UReadyPlayerMeSettings* Settings = GetMutableDefault<UReadyPlayerMeSettings>();
	if (Settings)
	{
		Settings->AvatarCacheSettings.bEnableAvatarCaching = bEnableCaching;
		Settings->SaveConfig();
	}
}

#if WITH_EDITOR
void UReadyPlayerMeSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	(void)SettingsChanged.ExecuteIfBound(PropertyChangedEvent.GetPropertyName());
}
#endif
