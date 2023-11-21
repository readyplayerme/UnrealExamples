// Copyright © 2023++ Ready Player Me

#include "PayloadExtractor.h"

#include "DataJsonUtils.h"
#include "Misc/DefaultValueHelper.h"
#include "Templates/SharedPointer.h"

namespace
{
	template <typename KeyType, typename ValueType>
	TMap<ValueType, KeyType> GetReverseMapping(const TMap<KeyType, ValueType>& InMap)
	{
		TMap<ValueType, KeyType> ReverseMapping;
		for (const auto& Item : InMap)
		{
			ReverseMapping.Add(Item.Value, Item.Key);
		}
		return ReverseMapping;
	}

	const TMap<EAvatarBodyType, FString> BODY_TYPE_TO_STRING_MAP =
	{
		{EAvatarBodyType::FullBody, "fullbody"},
		{EAvatarBodyType::HalfBody, "halfbody"},
	};
	const TMap<FString, EAvatarBodyType> STRING_TO_BODY_TYPE_MAP = GetReverseMapping(BODY_TYPE_TO_STRING_MAP);
	const TMap<EAvatarGender, FString> GENDER_TO_STRING_MAP =
	{
		{EAvatarGender::Masculine, "male"},
		{EAvatarGender::Feminine, "female"},
	};
	const TMap<FString, EAvatarGender> STRING_TO_GENDER_MAP = GetReverseMapping(GENDER_TO_STRING_MAP);

	EAvatarBodyType StringToBodyType(const FString& BodyTypeField)
	{
		return STRING_TO_BODY_TYPE_MAP.Contains(BodyTypeField) ? STRING_TO_BODY_TYPE_MAP[BodyTypeField] : EAvatarBodyType::Undefined;
	}

	EAvatarGender StringToGender(const FString& GenderField)
	{
		return STRING_TO_GENDER_MAP.Contains(GenderField) ? STRING_TO_GENDER_MAP[GenderField] : EAvatarGender::Undefined;
	}

	FString BodyTypeToString(EAvatarBodyType BodyType)
	{
		return BODY_TYPE_TO_STRING_MAP.Contains(BodyType) ? BODY_TYPE_TO_STRING_MAP[BodyType] : "";
	}

	FString GenderToString(EAvatarGender Gender)
	{
		return GENDER_TO_STRING_MAP.Contains(Gender) ? GENDER_TO_STRING_MAP[Gender] : "";
	}

	const TMap<ERpmPartnerAssetType, FString> ASSET_TYPE_TO_STRING_MAP =
	{
		{ERpmPartnerAssetType::BeardStyle, "beardStyle"},
		{ERpmPartnerAssetType::EyeColor, "eyeColor"},
		{ERpmPartnerAssetType::EyeShape, "eyeShape"},
		{ERpmPartnerAssetType::EyebrowStyle, "eyebrowStyle"},
		{ERpmPartnerAssetType::FaceMask, "faceMask"},
		{ERpmPartnerAssetType::FaceShape, "faceShape"},
		{ERpmPartnerAssetType::Glasses, "glasses"},
		{ERpmPartnerAssetType::HairStyle, "hairStyle"},
		{ERpmPartnerAssetType::Headwear, "headwear"},
		{ERpmPartnerAssetType::Facewear, "facewear"},
		{ERpmPartnerAssetType::LipShape, "lipShape"},
		{ERpmPartnerAssetType::NoseShape, "noseShape"},
		{ERpmPartnerAssetType::Outfit, "outfit"},
		{ERpmPartnerAssetType::Top, "top"},
		{ERpmPartnerAssetType::Bottom, "bottom"},
		{ERpmPartnerAssetType::Footwear, "footwear"},
		{ERpmPartnerAssetType::Shirt, "shirt"}
	};
	const TMap<ERpmPartnerAssetColor, FString> ASSET_COLOR_TO_STRING_MAP =
	{
		{ERpmPartnerAssetColor::BeardColor, "beardColor"},
		{ERpmPartnerAssetColor::EyebrowColor, "eyebrowColor"},
		{ERpmPartnerAssetColor::HairColor, "hairColor"},
		{ERpmPartnerAssetColor::SkinColor, "skinColor"},
	};
}

EAvatarGender FPayloadExtractor::GetGenderFromString(const FString& GenderStr)
{
	return StringToGender(GenderStr);
}

FString FPayloadExtractor::GetStringFromGender(EAvatarGender Gender)
{
	return GenderToString(Gender);
}

FRpmAvatarProperties FPayloadExtractor::ExtractPayload(const FString& JsonString)
{
	const TSharedPtr<FJsonObject> DataObject = FDataJsonUtils::ExtractDataObject(JsonString);
	if (!DataObject || !DataObject->HasField("assets"))
	{
		return {};
	}

	FRpmAvatarProperties AvatarProperties;
	AvatarProperties.Id = DataObject->GetStringField("id");
	AvatarProperties.Partner = DataObject->GetStringField("partner");
	AvatarProperties.Gender = StringToGender(DataObject->GetStringField("gender"));
	AvatarProperties.BodyType = StringToBodyType(DataObject->GetStringField("bodyType"));
	const auto AssetsObject = DataObject->GetObjectField("assets");
	for (const auto& Item : ASSET_TYPE_TO_STRING_MAP)
	{
		if (AssetsObject->HasField(Item.Value))
		{
			const FString AssetStr = AssetsObject->GetStringField(Item.Value);
			if (!AssetStr.IsEmpty())
			{
				int64 AssetId = 0;
				FDefaultValueHelper::ParseInt64(AssetsObject->GetStringField(Item.Value), AssetId);
				AvatarProperties.Assets.Add(Item.Key, AssetId);
			}
		}
	}
	for (const auto& Item : ASSET_COLOR_TO_STRING_MAP)
	{
		if (AssetsObject->HasField(Item.Value))
		{
			AvatarProperties.Colors.Add(Item.Key, AssetsObject->GetNumberField(Item.Value));
		}
	}

	return AvatarProperties;
}

FString FPayloadExtractor::MakeCreatePayload(const FRpmAvatarProperties& AvatarProperties)
{
	const TSharedPtr<FJsonObject> DataObject = MakeShared<FJsonObject>();
	const TSharedPtr<FJsonObject> AssetsObject = MakeShared<FJsonObject>();

	DataObject->SetObjectField("assets", AssetsObject);

	DataObject->SetStringField("partner", AvatarProperties.Partner);
	DataObject->SetStringField("bodyType", BodyTypeToString(AvatarProperties.BodyType));
	if (!AvatarProperties.Base64Image.IsEmpty())
	{
		DataObject->SetStringField("base64Image", AvatarProperties.Base64Image);
		DataObject->SetStringField("gender",  GenderToString(AvatarProperties.Gender));
	}

	return FDataJsonUtils::MakeDataPayload(DataObject);
}

FString FPayloadExtractor::MakeUpdatePayload(const TSharedPtr<FJsonObject> AssetsObject)
{
	const TSharedPtr<FJsonObject> DataObject = MakeShared<FJsonObject>();
	DataObject->SetObjectField("assets", AssetsObject);

	return FDataJsonUtils::MakeDataPayload(DataObject);
}
FString FPayloadExtractor::MakeUpdatePayload(ERpmPartnerAssetType AssetType, int64 AssetId)
{
	const TSharedPtr<FJsonObject> AssetsObject = MakeShared<FJsonObject>();
	const FString AssetIdStr = AssetId != 0 ? FString::FromInt(AssetId) : "";
	AssetsObject->SetStringField(ASSET_TYPE_TO_STRING_MAP[AssetType], AssetIdStr);
	if (AssetType == ERpmPartnerAssetType::Top || AssetType == ERpmPartnerAssetType::Bottom || AssetType == ERpmPartnerAssetType::Footwear)
	{
		AssetsObject->SetStringField(ASSET_TYPE_TO_STRING_MAP[ERpmPartnerAssetType::Outfit], "");
	}
	else if (AssetType == ERpmPartnerAssetType::Outfit)
	{
		AssetsObject->SetStringField(ASSET_TYPE_TO_STRING_MAP[ERpmPartnerAssetType::Top], "");
		AssetsObject->SetStringField(ASSET_TYPE_TO_STRING_MAP[ERpmPartnerAssetType::Bottom], "");
		AssetsObject->SetStringField(ASSET_TYPE_TO_STRING_MAP[ERpmPartnerAssetType::Footwear], "");
	}
	return MakeUpdatePayload(AssetsObject);
}

FString FPayloadExtractor::MakeUpdatePayload(ERpmPartnerAssetColor AssetColor, int32 ColorId)
{
	const TSharedPtr<FJsonObject> AssetsObject = MakeShared<FJsonObject>();
	AssetsObject->SetNumberField(ASSET_COLOR_TO_STRING_MAP[AssetColor], ColorId);
	return MakeUpdatePayload(AssetsObject);
}

FString FPayloadExtractor::MakePrecompilePayload(ERpmPartnerAssetType PrecompileAssetType, const TArray<FRpmPartnerAsset>& FilteredAssets)
{
	TArray<TSharedPtr<FJsonValue>> PreloadAssetString;
	for (const FRpmPartnerAsset& Asset : FilteredAssets)
	{
		if (PrecompileAssetType == Asset.AssetType)
		{
			const FString AssetStr = FString::Printf(TEXT("%lld"), Asset.Id);
			PreloadAssetString.Add(MakeShared<FJsonValueString>(AssetStr));
		}
	}
	const TSharedPtr<FJsonObject> DataObject = MakeShared<FJsonObject>();
	DataObject->SetArrayField(ASSET_TYPE_TO_STRING_MAP[PrecompileAssetType], PreloadAssetString);
	return FDataJsonUtils::MakeDataPayload(DataObject);
}
