// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealExamples/Public/WebViewEvents.h"
#include "Dom/JsonObject.h"

const FString WebViewEvents::AVATAR_EXPORT = TEXT("v1.avatar.exported");
const FString WebViewEvents::USER_SET = TEXT("v1.user.set");
const FString WebViewEvents::USER_AUTHORIZED = TEXT("v1.user.authorized");
const FString WebViewEvents::ASSET_UNLOCK = TEXT("v1.asset.unlock");

const FString DataField = "data";
const FString TypeField = "type";
const FString SourceField = "source";
const FString EventNameField = "eventName";

WebViewEvents::WebViewEvents()
{
}

WebViewEvents::~WebViewEvents()
{
}

FWebMessage WebViewEvents::ConvertJsonStringToWebMessage(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FWebMessage WebMessage;
		UE_LOG(LogTemp, Warning, TEXT("JSON = %s"), *JsonString);
		
		// Mandatory fields. Assuming they are always there.
		WebMessage.source = JsonObject->GetStringField(SourceField);
		WebMessage.eventName = JsonObject->GetStringField(EventNameField);

		// Optional field.
		if(JsonObject->HasField(TypeField))
		{
			WebMessage.type = JsonObject->GetStringField(TypeField);
		}

		if(JsonObject->HasField(DataField))
		{
			const TSharedPtr<FJsonObject> DataObject = JsonObject->GetObjectField(DataField);

			for (auto& Pair : DataObject->Values)
			{
				FString Key = Pair.Key;
				FString Value = Pair.Value->AsString();
				WebMessage.data.Add(Key, Value);
			}
		}

		return WebMessage;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Failed to parse JSON: %s"), *JsonString);
	return FWebMessage();
}

