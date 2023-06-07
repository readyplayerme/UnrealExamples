// Fill out your copyright notice in the Description page of Project Settings.


#include "WebMessage.h"
#include "WebViewEvents.h"

const char* KeyId = "id";
const char* KeyUserId = "userId";
const char* KeyUrl = "url";
const char* KeyAssetId = "assetId";

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
