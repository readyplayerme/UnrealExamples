// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeAnalyticsData.h"

class FJsonObject;

class FReadyPlayerMeAmplitudeEventLogger
{
public:
	FReadyPlayerMeAmplitudeEventLogger();

	void LogEvent(const FString& EventName, const TSharedPtr<FJsonObject>& Params = nullptr) const;
	TSharedRef<FJsonObject> MakeUserPropertiesJson() const;

	void SetAnalyticsTarget(const FString& Target);

private:
	TSharedRef<FJsonObject> MakeEventJson(const FString& EventName) const;
	void SendEvent(TSharedRef<FJsonObject> EventJson) const;

	static FString JsonToString(const TSharedRef<FJsonObject> JsonObject);
	static void SendHttpRequest(const FString& Url, const FString& Content);

	const int64 SessionId;
	FString AnalyticsTarget;
	const FReadyPlayerMeAnalyticsData AnalyticsData;
};
