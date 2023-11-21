// Copyright © 2023++ Ready Player Me


#include "DataJsonUtils.h"

#include "Templates/SharedPointer.h"
#include "Serialization/JsonReader.h"
#include "RpmAvatarCreatorTypes.h"

namespace
{
	const FString JSON_FIELD_DATA = "data";
}


TArray<TSharedPtr<FJsonValue>> FDataJsonUtils::ExtractDataArray(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), JsonObject) || !JsonObject->HasField(JSON_FIELD_DATA))
	{
		return {};
	}
	
	return JsonObject->GetArrayField(JSON_FIELD_DATA);
}

TSharedPtr<FJsonObject> FDataJsonUtils::ExtractDataObject(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;

	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), JsonObject) || !JsonObject->HasField(JSON_FIELD_DATA))
	{
		return {};
	}

	return JsonObject->GetObjectField(JSON_FIELD_DATA);
}

FString FDataJsonUtils::MakeDataPayload(const TSharedPtr<FJsonObject> DataObject)
{
	FString OutputJsonString;

	const TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetObjectField(JSON_FIELD_DATA, DataObject);

	if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&OutputJsonString)))
	{
		UE_LOG(LogRpmAvatarCreator, Warning, TEXT("Failed to create a valid url"));
	}
	return OutputJsonString;
}
