// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "AmplitudeEventLogger.h"
#include "ReadyPlayerMeEditorTypes.h"

class FAnalyticsEventLogger
{
public:
	static FAnalyticsEventLogger& Get();

	void LogProperties() const;
	void LogEvent(ERpmAnalyticsEventType EventType) const;
	void LogEnableAvatarCaching(bool bEnabled) const;
	void SetEnabled(bool bEnabled);
	void SetAnalyticsTarget(const FString& Target);
	void EnableAnalytics();

private:
	FAmplitudeEventLogger Logger;
	bool bIsEnabled = false;
};
