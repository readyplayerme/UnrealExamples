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

FWebMessage WebViewEvents::ConvertJsonStringToWebMessage(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FWebMessage WebMessage;
		
		WebMessage.Source = JsonObject->GetStringField(SourceField);
		WebMessage.EventName = JsonObject->GetStringField(EventNameField);
		
		if(JsonObject->HasField(TypeField))
		{
			WebMessage.Type = JsonObject->GetStringField(TypeField);
		}

		if(JsonObject->HasField(DataField))
		{
			const TSharedPtr<FJsonObject> DataObject = JsonObject->GetObjectField(DataField);

			for (const auto& Pair : DataObject->Values)
			{
				FString Key = Pair.Key;
				FString Value = Pair.Value->AsString();
				WebMessage.Data.Add(Key, Value);
			}
		}

		return WebMessage;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Failed to parse JSON: %s"), *JsonString);
	return FWebMessage();
}

