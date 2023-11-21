// Copyright © 2021++ Ready Player Me

#pragma once

#include "RpmWebViewTypes.h"

class FWebMessage
{
public:
	FString Type;
	FString EventName;
	TMap<FString, FString> Data;


	FString GetDataValue(const FString& Key) const;
	FString GetId() const;
	FString GetUserId() const;
	FString GetUrl() const;
	FAssetRecord GetAssetRecord() const;

private:
	static const char* KeyId;
	static const char* KeyUserId;
	static const char* KeyUrl;
	static const char* KeyAssetId;
};
