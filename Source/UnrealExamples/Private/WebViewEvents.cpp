// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealExamples/Public/WebViewEvents.h"
#include "Dom/JsonObject.h"
#include "JsonUtilities/Public/JsonUtilities.h"

const FString WebViewEvents::AVATAR_EXPORT = TEXT("v1.avatar.exported");
const FString WebViewEvents::USER_SET = TEXT("v1.user.set");
const FString WebViewEvents::USER_AUTHORIZED = TEXT("v1.user.authorized");
const FString WebViewEvents::ASSET_UNLOCK = TEXT("v1.asset.unlock");

WebViewEvents::WebViewEvents()
{
}

WebViewEvents::~WebViewEvents()
{
}

FWebMessage WebViewEvents::ConvertJsonStringToWebMessage(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FWebMessage WebMessage;

		WebMessage.type = JsonObject->GetStringField("type");
		WebMessage.source = JsonObject->GetStringField("source");
		WebMessage.eventName = JsonObject->GetStringField("eventName");

		const TSharedPtr<FJsonObject> DataObject = JsonObject->GetObjectField("data");

		for (auto& Pair : DataObject->Values)
		{
			FString Key = Pair.Key;
			FString Value = Pair.Value->AsString();
			WebMessage.data.Add(Key, Value);
		}

		return WebMessage;
	}
	else
	{
		// Handle the case where the JSON couldn't be deserialized
		UE_LOG(LogTemp, Warning, TEXT("Failed to parse JSON"));
		return FWebMessage();
	}
}
