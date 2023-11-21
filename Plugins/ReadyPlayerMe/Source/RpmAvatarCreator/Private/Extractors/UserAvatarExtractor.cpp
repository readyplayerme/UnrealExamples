// Copyright © 2023++ Ready Player Me


#include "UserAvatarExtractor.h"

#include "DataJsonUtils.h"
#include "Requests/Endpoints.h"
#include "Templates/SharedPointer.h"

namespace
{
	const FString JSON_FIELD_PARTNER = "partner";
	const FString JSON_FIELD_ID = "id";
}

TArray<FRpmUserAvatar> FUserAvatarExtractor::ExtractUserAvatars(const FString& JsonString)
{
	const TArray<TSharedPtr<FJsonValue>> JsonArray = FDataJsonUtils::ExtractDataArray(JsonString);
	TArray<FRpmUserAvatar> UserAvatars;
	for (const auto& JsonValue : JsonArray)
	{
		const auto JsonObject = JsonValue->AsObject();
		if (JsonObject->HasTypedField<EJson::String>(JSON_FIELD_PARTNER) && JsonObject->HasTypedField<EJson::String>(JSON_FIELD_ID))
		{
			FRpmUserAvatar UserAvatar;
			UserAvatar.Partner = JsonObject->GetStringField(JSON_FIELD_PARTNER);
			UserAvatar.Id = JsonObject->GetStringField(JSON_FIELD_ID);
			UserAvatar.ImageUrl = FEndpoints::GetRenderEndpoint(UserAvatar.Id);
			UserAvatars.Add(UserAvatar);
		}
	}
	return UserAvatars;
}
