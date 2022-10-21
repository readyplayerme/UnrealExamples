// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeSettings.h"

UReadyPlayerMeSettings::UReadyPlayerMeSettings()
	: bEnableAvatarCaching(false)
{
}

#if WITH_EDITOR
void UReadyPlayerMeSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	(void)SettingsChanged.ExecuteIfBound(PropertyChangedEvent.GetPropertyName());
}
#endif
