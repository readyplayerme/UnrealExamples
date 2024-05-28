// Copyright © 2024 Ready Player Me


#include "AvatarManifestExtractor.h"

#include "ReadyPlayerMeTypes.h"
#include "Serialization/JsonSerializer.h"

static const FString JSON_AVATAR_RECORDS = "AvatarRecords";
static const FString JSON_ID = "id";
static const FString JSON_USED_TS = "UsedTs";

TMap<FString, int64> FAvatarManifestExtractor::ExtractAvatarManifest(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject->HasField(JSON_AVATAR_RECORDS))
	{
		return {};
	}

	TMap<FString, int64> AvatarRecords;
	const TArray<TSharedPtr<FJsonValue>> RecordsJson = JsonObject->GetArrayField(JSON_AVATAR_RECORDS);
	for (const auto& JsonValue : RecordsJson)
	{
		const auto JsonValueObject = JsonValue->AsObject();
		if (JsonValueObject->HasTypedField<EJson::String>(JSON_ID) && JsonValueObject->HasTypedField<EJson::Number>(JSON_USED_TS))
		{
			const FString AvatarId = JsonValueObject->GetStringField(JSON_ID);
			const int64 UpdatedTimestamp = JsonValueObject->GetNumberField(JSON_USED_TS);
			AvatarRecords.Add(AvatarId, UpdatedTimestamp);
		}
	}

	return AvatarRecords;
}

FString FAvatarManifestExtractor::SerializeAvatarManifest(const TMap<FString, int64>& AvatarRecords)
{
	FString OutputJsonString;

	const TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

	TArray<TSharedPtr<FJsonValue>> RecordObjects;
	for (const auto& AvatarRecord: AvatarRecords)
	{
		const TSharedPtr<FJsonObject> RecordJson = MakeShared<FJsonObject>();
		RecordJson->SetStringField(JSON_ID, AvatarRecord.Key);
		RecordJson->SetNumberField(JSON_USED_TS, AvatarRecord.Value);
		RecordObjects.Add(MakeShared<FJsonValueObject>(RecordJson));
	}
	JsonObject->SetArrayField(JSON_AVATAR_RECORDS, RecordObjects);

	if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&OutputJsonString)))
	{
		UE_LOG(LogReadyPlayerMe, Warning, TEXT("Failed to create a valid json"));
	}
	return OutputJsonString;
}
