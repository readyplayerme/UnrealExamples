// Copyright © 2024 Ready Player Me

#include "ReadyPlayerMeEditorSettings.h"
#include "Analytics/AnalyticsSetup.h"
#include "Analytics/AnalyticsEventLogger.h"

UReadyPlayerMeEditorSettings::UReadyPlayerMeEditorSettings()
	: bEnableAnalytics(false)
{
}

#if WITH_EDITOR
void UReadyPlayerMeEditorSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (bEnableAnalytics)
	{
		FAnalyticsEventLogger::Get().EnableAnalytics();
		FAnalyticsSetup::RemoveWidget();
	}
	else
	{
		FAnalyticsEventLogger::Get().SetEnabled(false);
	}
}
#endif
