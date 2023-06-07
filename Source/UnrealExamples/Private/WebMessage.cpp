// Copyright © 2021++ Ready Player Me

#include "WebMessage.h"
#include "WebViewEvents.h"

const char* WebMessage::KeyId = "id";
const char* WebMessage::KeyUserId = "userId";
const char* WebMessage::KeyUrl = "url";
const char* WebMessage::KeyAssetId = "assetId";

FString WebMessage::GetDataValue(const FString& Key)
{
	if (Data.Contains(Key))
	{
		return *Data.Find(Key);
	}

	return FString();
}

FString WebMessage::GetId()
{
	return GetDataValue(KeyId);
}

FString WebMessage::GetUserId()
{
	return GetDataValue(KeyUserId);
}

FString WebMessage::GetUrl()
{
	return GetDataValue(KeyUrl);
}

FAssetRecord WebMessage::GetAssetRecord()
{
	FAssetRecord Record;
	Record.UserId = GetDataValue(KeyUserId);
	Record.AssetId = GetDataValue(KeyAssetId);
	return Record;
}
