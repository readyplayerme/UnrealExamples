// Copyright © 2021++ Ready Player Me

#include "UnrealExamples/Public/WebViewEvents.h"
#include "WebMessage.h"
#include "Dom/JsonObject.h"

const FString WebViewEvents::AVATAR_EXPORT = TEXT("v1.avatar.exported");
const FString WebViewEvents::USER_SET = TEXT("v1.user.set");
const FString WebViewEvents::USER_AUTHORIZED = TEXT("v1.user.authorized");
const FString WebViewEvents::ASSET_UNLOCK = TEXT("v1.asset.unlock");
const FString WebViewEvents::DATA_FIELD = "data";
const FString WebViewEvents::TYPE_FIELD = "type";
const FString WebViewEvents::SOURCE_FIELD = "source";
const FString WebViewEvents::EVENT_NAME_FIELD = "eventName";

WebMessage WebViewEvents::ConvertJsonStringToWebMessage(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		WebMessage WebMessage;

		WebMessage.Source = JsonObject->GetStringField(SOURCE_FIELD);
		WebMessage.EventName = JsonObject->GetStringField(EVENT_NAME_FIELD);

		if (JsonObject->HasField(TYPE_FIELD))
		{
			WebMessage.Type = JsonObject->GetStringField(TYPE_FIELD);
		}

		if (JsonObject->HasField(DATA_FIELD))
		{
			const TSharedPtr<FJsonObject> DataObject = JsonObject->GetObjectField(DATA_FIELD);

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
	return WebMessage();
}
