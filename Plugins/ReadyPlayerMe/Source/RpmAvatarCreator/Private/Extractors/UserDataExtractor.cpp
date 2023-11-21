// Copyright © 2023++ Ready Player Me


#include "UserDataExtractor.h"

#include "DataJsonUtils.h"
#include "Templates/SharedPointer.h"

static const FString JSON_FIELD_TOKEN = "token";
static const FString JSON_FIELD_REFRESH_TOKEN = "refreshToken";
static const FString JSON_FIELD_EMAIL = "email";
static const FString JSON_FIELD_CODE = "code";
static const FString JSON_FIELD_NAME = "name";
static const FString JSON_FIELD_ID = "id";
static const FString JSON_FIELD_AUTH_TYPE = "authType";

FRpmUserData FUserDataExtractor::ExtractAnonymousUserData(const FString& JsonString)
{
	const TSharedPtr<FJsonObject> DataObject = FDataJsonUtils::ExtractDataObject(JsonString);
	if (!DataObject || !DataObject->HasField(JSON_FIELD_ID) || !DataObject->HasField(JSON_FIELD_TOKEN))
	{
		return {};
	}

	FRpmUserData UserData;
	UserData.bIsAuthenticated = true;
	UserData.bIsExistingUser = false;
	UserData.Id = DataObject->GetStringField(JSON_FIELD_ID);
	UserData.Token = DataObject->GetStringField(JSON_FIELD_TOKEN);
	return UserData;
}

FRpmUserData FUserDataExtractor::ExtractRefreshedUserSession(const FString& JsonString)
{
	const TSharedPtr<FJsonObject> DataObject = FDataJsonUtils::ExtractDataObject(JsonString);
	if (!DataObject || !DataObject->HasField(JSON_FIELD_REFRESH_TOKEN) || !DataObject->HasField(JSON_FIELD_TOKEN))
	{
		return {};
	}

	FRpmUserData UserData;
	UserData.bIsAuthenticated = true;
	UserData.RefreshToken = DataObject->GetStringField(JSON_FIELD_REFRESH_TOKEN);
	UserData.Token = DataObject->GetStringField(JSON_FIELD_TOKEN);
	return UserData;
}

FRpmUserData FUserDataExtractor::ExtractUserData(const FString& JsonString)
{
	const TSharedPtr<FJsonObject> DataObject = FDataJsonUtils::ExtractDataObject(JsonString);
	if (!DataObject || !DataObject->HasField("_id") || !DataObject->HasField(JSON_FIELD_TOKEN))
	{
		return {};
	}

	FRpmUserData UserData;
	UserData.bIsAuthenticated = true;
	UserData.bIsExistingUser = true;
	UserData.Id = DataObject->GetStringField("_id");
	UserData.Name = DataObject->GetStringField(JSON_FIELD_NAME);
	UserData.Email = DataObject->GetStringField(JSON_FIELD_EMAIL);
	UserData.Token = DataObject->GetStringField(JSON_FIELD_TOKEN);
	UserData.RefreshToken = DataObject->GetStringField(JSON_FIELD_REFRESH_TOKEN);
	return UserData;
}

FString FUserDataExtractor::MakeAuthStartPayload(const FString& Email, const FString& UserId, bool bIsTypeCode)
{
	const TSharedPtr<FJsonObject> DataObject = MakeShared<FJsonObject>();
	DataObject->SetStringField(JSON_FIELD_EMAIL, Email);
	if (!UserId.IsEmpty())
	{
		DataObject->SetStringField(JSON_FIELD_ID, UserId);
	}
	if (bIsTypeCode)
	{
		DataObject->SetStringField(JSON_FIELD_AUTH_TYPE, JSON_FIELD_CODE);
	}
	return FDataJsonUtils::MakeDataPayload(DataObject);
}

FString FUserDataExtractor::MakeConfirmCodePayload(const FString& Code)
{
	const TSharedPtr<FJsonObject> DataObject = MakeShared<FJsonObject>();
	DataObject->SetStringField(JSON_FIELD_CODE, Code);
	return FDataJsonUtils::MakeDataPayload(DataObject);
}

FString FUserDataExtractor::MakeTokenRefreshPayload(const FRpmUserData& UserData)
{
	const TSharedPtr<FJsonObject> DataObject = MakeShared<FJsonObject>();
	DataObject->SetStringField(JSON_FIELD_REFRESH_TOKEN, UserData.RefreshToken);
	DataObject->SetStringField(JSON_FIELD_TOKEN, UserData.Token);
	return FDataJsonUtils::MakeDataPayload(DataObject);
}
