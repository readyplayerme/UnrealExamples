// Copyright © 2021++ Ready Player Me

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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAvatarCreated, const FString&, AvatarUrl);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserSet, const FString&, UserId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAssetUnlock, const FAssetRecord&, AssetId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserAuthorized, const FString&, UserId);

class UNREALEXAMPLES_API WebViewEvents
{
public:
	static class WebMessage ConvertJsonStringToWebMessage(const FString& JsonString);

	static const FString AVATAR_EXPORT;
	static const FString USER_SET;
	static const FString USER_AUTHORIZED;
	static const FString ASSET_UNLOCK;
	
private:
	static const FString DATA_FIELD;
	static const FString TYPE_FIELD;
	static const FString SOURCE_FIELD;
	static const FString EVENT_NAME_FIELD;
};
