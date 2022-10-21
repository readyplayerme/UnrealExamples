// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeAnalyticsEventLogger.h"
#include "ReadyPlayerMeAmplitudeEventLogger.h"
#include "Kismet/KismetStringLibrary.h"

static const FString EVENT_OPEN_PROJECT = "open project";
static const FString EVENT_CLOSE_PROJECT = "close project";
static const FString EVENT_ENABLE_CACHING = "enable caching";
static const FString EVENT_SET_USER_PROPERTIES = "set user properties";
static const FString EVENT_ALLOW_LOGGING = "allow tracking";

static const FString JSON_CACHING_ENABLED = "caching enabled";

FReadyPlayerMeAnalyticsEventLogger& FReadyPlayerMeAnalyticsEventLogger::Get()
{
	static FReadyPlayerMeAnalyticsEventLogger EventLogger;
	return EventLogger;
}

void FReadyPlayerMeAnalyticsEventLogger::LogOpenProject() const
{
	if (!bIsEnabled)
	{
		return;
	}
	Logger.LogEvent(EVENT_SET_USER_PROPERTIES, Logger.MakeUserPropertiesJson());
	Logger.LogEvent(EVENT_OPEN_PROJECT);
}

void FReadyPlayerMeAnalyticsEventLogger::LogCloseProject() const
{
	if (!bIsEnabled)
	{
		return;
	}
	Logger.LogEvent(EVENT_CLOSE_PROJECT);
}

void FReadyPlayerMeAnalyticsEventLogger::LogEnableAvatarCaching(bool bEnabled) const
{
	if (!bIsEnabled)
	{
		return;
	}
	const auto JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(JSON_CACHING_ENABLED, UKismetStringLibrary::Conv_BoolToString(bEnabled));
	Logger.LogEvent(EVENT_ENABLE_CACHING, JsonObject);
}

void FReadyPlayerMeAnalyticsEventLogger::SetEnabled(bool bEnabled)
{
	bIsEnabled = bEnabled;
}

void FReadyPlayerMeAnalyticsEventLogger::SetAnalyticsTarget(const FString& Target)
{
	Logger.SetAnalyticsTarget(Target);
}

void FReadyPlayerMeAnalyticsEventLogger::EnableAnalytics()
{
	bIsEnabled = true;
	Logger.LogEvent(EVENT_ALLOW_LOGGING, Logger.MakeUserPropertiesJson());
}
