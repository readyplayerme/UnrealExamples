// Copyright © 2023++ Ready Player Me


#include "AvatarTemplateExtractor.h"

#include "DataJsonUtils.h"
#include "PayloadExtractor.h"
#include "Templates/SharedPointer.h"

namespace
{
	const FString JSON_FIELD_IMAGE_URL = "imageUrl";
	const FString JSON_FIELD_ID = "id";
	const FString JSON_FIELD_GENDER = "gender";
}

TArray<FRpmAvatarTemplate> FAvatarTemplateExtractor::ExtractAvatarTemplates(const FString& JsonString)
{
	const TArray<TSharedPtr<FJsonValue>> JsonArray = FDataJsonUtils::ExtractDataArray(JsonString);
	TArray<FRpmAvatarTemplate> AvatarTemplates;
	for (const auto& JsonValue : JsonArray)
	{
		const auto JsonObject = JsonValue->AsObject();
		if (JsonObject->HasTypedField<EJson::String>(JSON_FIELD_IMAGE_URL) && JsonObject->HasTypedField<EJson::String>(JSON_FIELD_ID))
		{
			FRpmAvatarTemplate AvatarTemplate;
			AvatarTemplate.ImageUrl = JsonObject->GetStringField(JSON_FIELD_IMAGE_URL);
			AvatarTemplate.Id = JsonObject->GetStringField(JSON_FIELD_ID);
			AvatarTemplate.Gender = FPayloadExtractor::GetGenderFromString(JsonObject->GetStringField(JSON_FIELD_GENDER));
			AvatarTemplates.Add(AvatarTemplate);
		}
	}
	return AvatarTemplates;
}
