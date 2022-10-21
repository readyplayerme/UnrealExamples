// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeAmplitudeEventLogger.h"
#include "ReadyPlayerMe/Private/Utils/ReadyPlayerMeRequestCreator.h"

#include "Templates/SharedPointer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Policies/CondensedJsonPrintPolicy.h"

static const FString ENDPOINT = "https://analytics-sdk.readyplayer.me/";
static const FString ANALYTICS_TARGET = "unreal";

static const FString JSON_EVENTS = "events";
static const FString JSON_TARGET = "target";

static const FString JSON_USER_PROPERTIES = "user_properties";

static const FString JSON_APP_NAME = "app name";
static const FString JSON_ENGINE_VERSION = "engine version";
static const FString JSON_SDK_TARGET = "sdk target";
static const FString JSON_SUBDOMAIN = "subdomain";
static const FString JSON_APP_IDENTIFIER = "app identifier";

static const FString JSON_EVENT_TYPE = "event_type";
static const FString JSON_SESSION_ID = "session_id";
static const FString JSON_DEVICE_ID = "device_id";
static const FString JSON_PLATFORM = "platform";
static const FString JSON_APP_VERSION = "app_version";
static const FString JSON_OPERATING_SYSTEM = "os_name";

constexpr float REQUEST_TIMEOUT = 5.f;

FReadyPlayerMeAmplitudeEventLogger::FReadyPlayerMeAmplitudeEventLogger()
	: SessionId(FDateTime::Now().ToUnixTimestamp())
	, AnalyticsTarget(ANALYTICS_TARGET)
{
}

void FReadyPlayerMeAmplitudeEventLogger::SetAnalyticsTarget(const FString& Target)
{
	AnalyticsTarget = Target;
}

TSharedRef<FJsonObject> FReadyPlayerMeAmplitudeEventLogger::MakeUserPropertiesJson() const
{
	const auto JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(JSON_APP_NAME, AnalyticsData.AppName);
	JsonObject->SetStringField(JSON_ENGINE_VERSION, AnalyticsData.UnrealVersion);
	JsonObject->SetStringField(JSON_SDK_TARGET, AnalyticsData.SdkTarget);
	JsonObject->SetStringField(JSON_SUBDOMAIN, AnalyticsData.Subdomain);
	JsonObject->SetStringField(JSON_APP_IDENTIFIER, AnalyticsData.AppIdentifier);
	return JsonObject;
}

TSharedRef<FJsonObject> FReadyPlayerMeAmplitudeEventLogger::MakeEventJson(const FString& EventName) const
{
	const auto JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(JSON_EVENT_TYPE, EventName);
	JsonObject->SetNumberField(JSON_SESSION_ID, SessionId);
	JsonObject->SetStringField(JSON_DEVICE_ID, AnalyticsData.DeviceId);
	JsonObject->SetStringField(JSON_PLATFORM, AnalyticsData.Platform);
	JsonObject->SetStringField(JSON_APP_VERSION, AnalyticsData.SDKVersion);
	JsonObject->SetStringField(JSON_OPERATING_SYSTEM, AnalyticsData.Platform);
	return JsonObject;
}

FString FReadyPlayerMeAmplitudeEventLogger::JsonToString(const TSharedRef<FJsonObject> JsonObject)
{
	FString JsonString;
	const auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonString);
	if (!FJsonSerializer::Serialize(JsonObject, Writer))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create a valid analytics data"));
	}
	return JsonString;
}

void FReadyPlayerMeAmplitudeEventLogger::LogEvent(const FString& EventName, const TSharedPtr<FJsonObject>& Params) const
{
	const auto EventJson = MakeEventJson(EventName);
	if (Params)
	{
		EventJson->SetObjectField(JSON_USER_PROPERTIES, Params);
	}
	SendEvent(EventJson);
}

void FReadyPlayerMeAmplitudeEventLogger::SendEvent(TSharedRef<FJsonObject> EventJson) const
{
	const auto JsonObject = MakeShared<FJsonObject>();
	const TArray<TSharedPtr<FJsonValue>> Events { MakeShared<FJsonValueObject>(EventJson) };
	JsonObject->SetStringField(JSON_TARGET, AnalyticsTarget);
	JsonObject->SetArrayField(JSON_EVENTS, Events);

	const auto Content = JsonToString(JsonObject);
	SendHttpRequest(ENDPOINT, Content);
}

void FReadyPlayerMeAmplitudeEventLogger::SendHttpRequest(const FString& Url, const FString& Content)
{
	auto HttpRequest = FReadyPlayerMeRequestCreator::MakeHttpRequest(Url, REQUEST_TIMEOUT);
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetHeader("Accept", "*/*");
	HttpRequest->SetContentAsString(Content);
	HttpRequest->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid())
			{
				UE_LOG(LogTemp, Display, TEXT("Failed to send an analytical event"));
			}
		});
	HttpRequest->ProcessRequest();
}
