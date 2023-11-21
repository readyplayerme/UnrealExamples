// Copyright © 2023++ Ready Player Me

#pragma once

#include "RpmWebViewTypes.generated.h"

UENUM(BlueprintType)
enum class ESelectBodyType : uint8
{
	None,
	Select,
	FullBody,
	HalfBody
};

UENUM(BlueprintType)
enum class ESelectGender : uint8
{
	None,
	Male,
	Female
};

UENUM(BlueprintType)
enum class ELanguage : uint8
{
	Default UMETA(DisplayName = "Default"),
	En UMETA(DisplayName = "English"),
	EnIe UMETA(DisplayName = "English (Ireland)"),
	De UMETA(DisplayName = "German"),
	Fr UMETA(DisplayName = "French"),
	Es UMETA(DisplayName = "Spanish"),
	EsMx UMETA(DisplayName = "Spanish (Mexican)"),
	Pt UMETA(DisplayName = "Portuguese"),
	PtBr UMETA(DisplayName = "Portuguese (Brazil)"),
	It UMETA(DisplayName = "Italian"),
	Tr UMETA(DisplayName = "Turkish"),
	Jp UMETA(DisplayName = "Japanese"),
	Kr UMETA(DisplayName = "Korean"),
	Ch UMETA(DisplayName = "Chinese"),
};

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
