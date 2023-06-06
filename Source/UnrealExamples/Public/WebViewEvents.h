// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WebViewEvents.generated.h"

USTRUCT(BlueprintType)
struct FAssetRecord
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ready Player Me|Web Browser")
	FString UserId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ready Player Me|Web Browser")
	FString AssetId;
};


USTRUCT()
struct FWebMessage
{
	GENERATED_BODY()

	UPROPERTY()
	FString Type;

	UPROPERTY()
	FString Source;

	UPROPERTY()
	FString EventName;

	UPROPERTY()
	TMap<FString, FString> Data;
	
	FString GetDataValue(const FString& Key) const
	{
		if (Data.Contains(Key))
		{
			return *Data.Find(Key);
		}
        
		return FString();
	}

	FString GetId() const
	{
		return GetDataValue("id");
	}

	FString GetUserId() const
	{
		return GetDataValue("userId");
	}

	FString GetUrl() const
	{
		return GetDataValue("url");
	}

	FAssetRecord GetAssetRecord() const
	{
		FAssetRecord Record;

		FString UserId = GetDataValue("userId");
		FString AssetId = GetDataValue("assetId");
		Record.UserId = UserId;
		Record.AssetId = AssetId;
		return Record;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAvatarCreated, const FString&, AvatarUrl);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserSet, const FString&, userId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAssetUnlock, const FAssetRecord&, assetId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserAuthorized, const FString&, userId);

class UNREALEXAMPLES_API WebViewEvents
{
public:
	
	static FWebMessage ConvertJsonStringToWebMessage(const FString& JsonString);
	
	static const FString AVATAR_EXPORT;
	static const FString USER_SET;
	static const FString USER_AUTHORIZED;
	static const FString ASSET_UNLOCK;
	static const FString ID;
};
