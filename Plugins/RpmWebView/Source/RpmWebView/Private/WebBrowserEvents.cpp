// Copyright © 2021++ Ready Player Me

#include "WebBrowserEvents.h"
#include "Dom/JsonObject.h"

const FString FWebViewEvents::AVATAR_EXPORT = TEXT("v1.avatar.exported");
const FString FWebViewEvents::USER_SET = TEXT("v1.user.set");
const FString FWebViewEvents::USER_AUTHORIZED = TEXT("v1.user.authorized");
const FString FWebViewEvents::ASSET_UNLOCK = TEXT("v1.asset.unlock");
const FString FWebViewEvents::DATA_FIELD = "data";
const FString FWebViewEvents::TYPE_FIELD = "type";
const FString FWebViewEvents::SOURCE_FIELD = "source";
const FString FWebViewEvents::EVENT_NAME_FIELD = "eventName";

FWebMessage FWebViewEvents::ConvertJsonStringToWebMessage(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FWebMessage WebMessage;
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
	return FWebMessage();
}
