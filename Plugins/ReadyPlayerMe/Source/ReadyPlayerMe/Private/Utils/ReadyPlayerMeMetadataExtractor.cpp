// Copyright © 2021++ Ready Player Me


#include "Utils/ReadyPlayerMeMetadataExtractor.h"

#include "glTFRuntimeAsset.h"
#include "Templates/SharedPointer.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

static const FString FULLBODY_BONE_NODE = "Armature";
static const FString HALFBODY_BONE_NODE = "AvatarRoot";
static const FString GENDER_FEMININE = "Feminine";
static const FString GENDER_MASCULINE = "Masculine";
static const FString TYPE_FULLBODY = "Fullbody";
static const FString TYPE_HALFBODY = "Halfbody";
static const FString JSON_FIELD_OUTFIT = "outfitVersion";
static const FString JSON_FIELD_BODY = "bodyType";
static const FString JSON_FIELD_GENDER = "outfitGender";
static const FString JSON_FIELD_MODIFIED_DATE = "lastModifiedDate";
static const int MAX_HALFBODY_NODES=60;

FString FReadyPlayerMeMetadataExtractor::GetRootBoneName(const EAvatarBodyType& AvatarBodyType)
{
	if (AvatarBodyType == EAvatarBodyType::FullBody)
	{
		return FULLBODY_BONE_NODE;
	}

	return HALFBODY_BONE_NODE;
}

EAvatarBodyType FReadyPlayerMeMetadataExtractor::GetBodyTypeFromAsset(UglTFRuntimeAsset* GltfRuntimeAsset)
{
	// Temporary solution for checking if the body type, without having the metadata.
	// This will also load all the nodes synchronously.
	if (GltfRuntimeAsset->GetNodes().Num() > MAX_HALFBODY_NODES)
	{
		return EAvatarBodyType::FullBody;
	}

	return EAvatarBodyType::HalfBody;
}

FString FReadyPlayerMeMetadataExtractor::AddModifiedDateToMetadataJson(const FString& JsonString, const FString& LastModifiedDate)
{
	FString OutputJsonString;
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		JsonObject->SetStringField(JSON_FIELD_MODIFIED_DATE, LastModifiedDate);

		const auto Writer = TJsonWriterFactory<>::Create(&OutputJsonString);
		if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
		{
			UE_LOG(LogReadyPlayerMe, Warning, TEXT("Failed to create a valid url"));
		}
	}
	return OutputJsonString;
}

FAvatarMetadata FReadyPlayerMeMetadataExtractor::ExtractAvatarMetadata(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	FAvatarMetadata Metadata;

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		if (JsonObject->HasField(JSON_FIELD_MODIFIED_DATE))
		{
			Metadata.LastModifiedDate = JsonObject->GetStringField(JSON_FIELD_MODIFIED_DATE);
		}
		if (JsonObject->HasField(JSON_FIELD_BODY))
		{
			const FString BodyTypeField = JsonObject->GetStringField(JSON_FIELD_BODY);
			if (BodyTypeField == TYPE_HALFBODY)
			{
				Metadata.BodyType = EAvatarBodyType::HalfBody;
			}
			else if (BodyTypeField == TYPE_FULLBODY)
			{
				Metadata.BodyType = EAvatarBodyType::FullBody;
			}
		}
		if (JsonObject->HasField(JSON_FIELD_OUTFIT))
		{
			Metadata.OutfitVersion = JsonObject->GetIntegerField(JSON_FIELD_OUTFIT);
		}
		if (JsonObject->HasField(JSON_FIELD_GENDER))
		{
			const FString GenderField = JsonObject->GetStringField(JSON_FIELD_GENDER);
			if (GenderField == GENDER_FEMININE)
			{
				Metadata.OutfitGender = EAvatarGender::Feminine;
			}
			else if (GenderField == GENDER_MASCULINE)
			{
				Metadata.OutfitGender = EAvatarGender::Masculine;
			}
		}
	}

	return Metadata;
}
