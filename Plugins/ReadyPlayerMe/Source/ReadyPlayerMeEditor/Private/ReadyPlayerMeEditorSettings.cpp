// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeEditorSettings.h"
#include "Analytics/ReadyPlayerMeAnalyticsSetup.h"
#include "Analytics/ReadyPlayerMeAnalyticsEventLogger.h"

UReadyPlayerMeEditorSettings::UReadyPlayerMeEditorSettings()
	: bEnableAnalytics(false)
	, bDontAskAgain(false)
{
}

void UReadyPlayerMeEditorSettings::EnableAnalytics() {
	UReadyPlayerMeEditorSettings* Settings = GetMutableDefault<UReadyPlayerMeEditorSettings>();
	if (Settings)
	{
		Settings->bEnableAnalytics = true;
		Settings->SaveConfig();
		FReadyPlayerMeAnalyticsEventLogger::Get().EnableAnalytics();
		FReadyPlayerMeAnalyticsSetup::RemoveWidget();
	}
}

void UReadyPlayerMeEditorSettings::SetDontAskAgain(bool bDontAsk)
{
	UReadyPlayerMeEditorSettings* Settings = GetMutableDefault<UReadyPlayerMeEditorSettings>();
	if (Settings)
	{
		Settings->bDontAskAgain = bDontAsk;
		Settings->SaveConfig();
		FReadyPlayerMeAnalyticsSetup::RemoveWidget();
	}
}

#if WITH_EDITOR
void UReadyPlayerMeEditorSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (bEnableAnalytics)
	{
		FReadyPlayerMeAnalyticsEventLogger::Get().EnableAnalytics();
		FReadyPlayerMeAnalyticsSetup::RemoveWidget();
	}
	else
	{
		FReadyPlayerMeAnalyticsEventLogger::Get().SetEnabled(false);
	}
}
#endif
