// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"

class UNREALEXAMPLES_API WebMessage
{
public:
	FString Type;
	FString Source;
	FString EventName;
	TMap<FString, FString> Data;


	FString GetDataValue(const FString& Key);
	FString GetId();
	FString GetUserId();
	FString GetUrl();
	struct FAssetRecord GetAssetRecord();

private:
	static const char* KeyId;
	static const char* KeyUserId;
	static const char* KeyUrl;
	static const char* KeyAssetId;
};
