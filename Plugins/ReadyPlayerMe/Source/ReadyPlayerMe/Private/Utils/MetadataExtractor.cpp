// Copyright © 2024 Ready Player Me


#include "MetadataExtractor.h"

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
static const FString JSON_FIELD_SKIN_TONE = "skinTone";
static const FString JSON_FIELD_BODY = "bodyType";
static const FString JSON_FIELD_GENDER = "outfitGender";
static const FString JSON_FIELD_UPDATED_AT = "updatedAt";
static const int MAX_HALFBODY_NODES=60;

FString FMetadataExtractor::GetRootBoneName(const EAvatarBodyType& AvatarBodyType)
{
	if (AvatarBodyType == EAvatarBodyType::FullBody)
	{
		return FULLBODY_BONE_NODE;
	}

	return HALFBODY_BONE_NODE;
}

EAvatarBodyType FMetadataExtractor::GetBodyTypeFromAsset(UglTFRuntimeAsset* GltfRuntimeAsset)
{
	// Temporary solution for checking if the body type, without having the metadata.
	// This will also load all the nodes synchronously.
	if (GltfRuntimeAsset->GetNodes().Num() > MAX_HALFBODY_NODES)
	{
		return EAvatarBodyType::FullBody;
	}

	return EAvatarBodyType::HalfBody;
}

FAvatarMetadata FMetadataExtractor::ExtractAvatarMetadata(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	FAvatarMetadata Metadata;

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		if (JsonObject->HasField(JSON_FIELD_UPDATED_AT))
		{
			Metadata.UpdatedAtDate = JsonObject->GetStringField(JSON_FIELD_UPDATED_AT);
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
		if (JsonObject->HasField(JSON_FIELD_SKIN_TONE))
		{
			Metadata.SkinTone = JsonObject->GetStringField(JSON_FIELD_SKIN_TONE);
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
