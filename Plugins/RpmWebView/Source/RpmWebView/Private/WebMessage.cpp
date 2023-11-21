// Copyright © 2021++ Ready Player Me

#include "WebMessage.h"

const char* FWebMessage::KeyId = "id";
const char* FWebMessage::KeyUserId = "userId";
const char* FWebMessage::KeyUrl = "url";
const char* FWebMessage::KeyAssetId = "assetId";

FString FWebMessage::GetDataValue(const FString& Key) const
{
	if (Data.Contains(Key))
	{
		return *Data.Find(Key);
	}

	return FString();
}

FString FWebMessage::GetId() const
{
	return GetDataValue(KeyId);
}

FString FWebMessage::GetUserId() const
{
	return GetDataValue(KeyUserId);
}

FString FWebMessage::GetUrl() const
{
	return GetDataValue(KeyUrl);
}

FAssetRecord FWebMessage::GetAssetRecord() const
{
	FAssetRecord Record;
	Record.UserId = GetDataValue(KeyUserId);
	Record.AssetId = GetDataValue(KeyAssetId);
	return Record;
}
