// Copyright © 2023++ Ready Player Me

#pragma once

#include "ReadyPlayerMeTypes.h"

#include "RpmAvatarCreatorTypes.generated.h"

USTRUCT(BlueprintType)
struct FRpmUserData
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ready Player Me")
	bool bIsAuthenticated;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ready Player Me")
	bool bIsExistingUser;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ready Player Me")
	FString Id;

	UPROPERTY()
	FString Token;

	UPROPERTY()
	FString RefreshToken;

	UPROPERTY()
	FString Subdomain;

	UPROPERTY()
	FString AppId;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ready Player Me")
	FString Name;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ready Player Me")
	FString Email;

	FRpmUserData()
	{
		bIsAuthenticated = false;
		bIsExistingUser = false;
	}
};

UENUM(BlueprintType)
enum class ERpmPartnerAssetType : uint8
{
	BeardStyle,
	EyeColor,
	EyeShape,
	EyebrowStyle,
	FaceMask,
	FaceShape,
	Glasses,
	HairStyle,
	Headwear,
	Facewear,
	LipShape,
	NoseShape,
	Outfit,
	Top,
	Bottom,
	Footwear,
	Shirt
};

UENUM(BlueprintType)
enum class ERpmPartnerAssetColor : uint8
{
	SkinColor,
	HairColor,
	BeardColor,
	EyebrowColor
};

USTRUCT(BlueprintType)
struct FRpmColorPalette
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ready Player Me")
	ERpmPartnerAssetColor AssetColor;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ready Player Me")
	TArray<FColor> RgbColors;

	FRpmColorPalette()
	{
		AssetColor = ERpmPartnerAssetColor::SkinColor;
	}
};

USTRUCT(BlueprintType)
struct FRpmPartnerAsset
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Ready Player Me")
	FString Id;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Ready Player Me")
	FString Name;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Ready Player Me")
	ERpmPartnerAssetType AssetType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Ready Player Me")
	EAvatarGender Gender;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Ready Player Me")
	FString IconUrl;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Ready Player Me")
	FString BadgeUrl;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Ready Player Me")
	bool bIsLocked;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Ready Player Me")
	FString Price;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Ready Player Me")
	bool bIsCustomizable;

	FRpmPartnerAsset()
	{
		Id = 0;
		AssetType = ERpmPartnerAssetType::FaceShape;
		Gender = EAvatarGender::Undefined;
		bIsLocked = false;
		bIsCustomizable = true;
	}
};

USTRUCT(BlueprintType)
struct FRpmAvatarProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	FString Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	FString Partner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	EAvatarGender Gender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	EAvatarBodyType BodyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	TMap<ERpmPartnerAssetColor, int32> Colors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	TMap<ERpmPartnerAssetType, FString> Assets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	FString Base64Image;

	FRpmAvatarProperties()
	{
		Gender = EAvatarGender::Undefined;
		BodyType = EAvatarBodyType::Undefined;
	}
};

USTRUCT(BlueprintType)
struct FRpmAvatarTemplate
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ready Player Me")
	FString Id;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ready Player Me")
	FString ImageUrl;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ready Player Me")
	EAvatarGender Gender;

	FRpmAvatarTemplate()
	{
		Gender = EAvatarGender::Undefined;
	}
};

USTRUCT(BlueprintType)
struct FRpmUserAvatar
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	FString Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	FString Partner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	FString ImageUrl;
};

UENUM(BlueprintType)
enum class ERpmAvatarCreatorError : uint8
{
	None,
	AuthenticationFailure,
	SendActivationCodeFailure,
	ConfirmActivationCodeFailure,
	AssetDownloadFailure,
	ColorDownloadFailure,
	AvatarTemplateFailure,
	UserAvatarDownloadFailure,
	MetadataDownloadFailure,
	AvatarCreateFailure,
	AvatarPreviewFailure,
	AvatarSaveFailure,
	AvatarDeleteFailure
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAvatarCreatorFailed, ERpmAvatarCreatorError, Error);

DECLARE_DYNAMIC_DELEGATE(FAuthenticationCompleted);

DECLARE_DYNAMIC_DELEGATE_OneParam(FAvatarSaveCompleted, const FString&, Url);

DECLARE_DYNAMIC_DELEGATE(FAvatarDeleteCompleted);

DECLARE_DYNAMIC_DELEGATE(FAvatarEditorReady);

DECLARE_DYNAMIC_DELEGATE(FUpdateLockedAssetsCompleted);

DECLARE_DYNAMIC_DELEGATE_OneParam(FUserAvatarsDownloadCompleted, const TArray<FRpmUserAvatar>&, UserAvatars);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FImageDownloadCompleted, UTexture2D*, Image, const FString&, Url);

DECLARE_DYNAMIC_DELEGATE_OneParam(FAvatarTemplatesDownloadCompleted, const TArray<FRpmAvatarTemplate>&, AvatarTemplates);

DECLARE_DELEGATE_OneParam(FBaseRequestCompleted, bool);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPreviewDownloadCompleted, const USkeletalMesh*, SkeletalMesh);

DECLARE_DYNAMIC_DELEGATE(FSessionExpired);

DECLARE_LOG_CATEGORY_EXTERN(LogRpmAvatarCreator, Log, All);
