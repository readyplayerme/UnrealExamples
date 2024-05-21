// Copyright © 2023++ Ready Player Me

#include "PartnerAssetExtractor.h"

#include "DataJsonUtils.h"
#include "PayloadExtractor.h"

#include "Templates/SharedPointer.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

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

	const TMap<FString, ERpmPartnerAssetType> STRING_TO_ASSET_TYPES_MAP =
	{
		{"beard", ERpmPartnerAssetType::BeardStyle},
		{"eye", ERpmPartnerAssetType::EyeColor},
		{"eyeshape", ERpmPartnerAssetType::EyeShape},
		{"eyebrows", ERpmPartnerAssetType::EyebrowStyle},
		{"facemask", ERpmPartnerAssetType::FaceMask},
		{"faceshape", ERpmPartnerAssetType::FaceShape},
		{"glasses", ERpmPartnerAssetType::Glasses},
		{"hair", ERpmPartnerAssetType::HairStyle},
		{"headwear", ERpmPartnerAssetType::Headwear},
		{"facewear", ERpmPartnerAssetType::Facewear},
		{"lipshape", ERpmPartnerAssetType::LipShape},
		{"noseshape", ERpmPartnerAssetType::NoseShape},
		{"outfit", ERpmPartnerAssetType::Outfit},
		{"top", ERpmPartnerAssetType::Top},
		{"bottom", ERpmPartnerAssetType::Bottom},
		{"footwear", ERpmPartnerAssetType::Footwear},
		{"shirt", ERpmPartnerAssetType::Shirt}
	};

	const TMap<ERpmPartnerAssetType, FString> ASSET_TYPES_TO_STRING_MAP = GetReverseMapping(STRING_TO_ASSET_TYPES_MAP);

	const TMap<ERpmPartnerAssetColor, FString> COLOR_TO_STRING_MAP =
	{
		{ERpmPartnerAssetColor::BeardColor, "beard"},
		{ERpmPartnerAssetColor::EyebrowColor, "eyebrow"},
		{ERpmPartnerAssetColor::HairColor, "hair"},
		{ERpmPartnerAssetColor::SkinColor, "skin"},
	};

	const FString JSON_FIELD_TYPE = "type";
	const FString JSON_FIELD_ID = "id";
	const FString JSON_FIELD_NAME = "name";
	const FString JSON_FIELD_GENDER = "gender";
	const FString JSON_FIELD_ICON_URL = "iconUrl";
	const FString JSON_FIELD_BADGE_LOGO_URL = "badgeLogoUrl";
	const FString JSON_FIELD_IS_LOCKED = "locked";
	const FString JSON_FIELD_IS_LOCKED_CATEGORIES = "lockedCategories";
	const FString JSON_FIELD_PRICE = "price";

	const FString JSON_PAGINATION = "pagination";
	const FString JSON_TOTAL_PAGES = "totalPages";
	const FString JSON_PAGE = "page";
	const FString JSON_HAS_NEXT_PAGE = "hasNextPage";
}

FString FPartnerAssetExtractor::GetStringFromAssetType(ERpmPartnerAssetType AssetType)
{
	return ASSET_TYPES_TO_STRING_MAP[AssetType];
}

TArray<FRpmColorPalette> FPartnerAssetExtractor::ExtractColors(const FString& JsonString)
{
	TArray<FRpmColorPalette> Colors;

	const TSharedPtr<FJsonObject> DataObject = FDataJsonUtils::ExtractDataObject(JsonString);
	if (!DataObject)
	{
		return {};
	}

	for (const auto& Item : COLOR_TO_STRING_MAP)
	{
		if (DataObject->HasTypedField<EJson::Array>(Item.Value))
		{
			TArray<FColor> ColorArray;
			for (const auto& ColorItem : DataObject->GetArrayField(Item.Value))
			{
				const FString ColorHex = ColorItem->AsString();
				ColorArray.Add(FColor::FromHex(ColorHex));
			}
			FRpmColorPalette Palette;
			Palette.AssetColor = Item.Key;
			Palette.RgbColors = ColorArray;
			Colors.Add(Palette);
		}
	}
	return Colors;
}

FAssetPaginationData FPartnerAssetExtractor::ExtractAssets(const FString& JsonString)
{
	FAssetPaginationData PaginationData;
	const TArray<TSharedPtr<FJsonValue>> JsonArray = FDataJsonUtils::ExtractDataArray(JsonString);

	for (const auto& JsonValue : JsonArray)
	{
		FRpmPartnerAsset Asset;
		const auto JsonObject = JsonValue->AsObject();
		if (JsonObject->HasTypedField<EJson::String>(JSON_FIELD_TYPE))
		{
			const FString AssetTypeStr = JsonObject->GetStringField(JSON_FIELD_TYPE);
			if (!STRING_TO_ASSET_TYPES_MAP.Contains(AssetTypeStr))
			{
				continue;
			}
			Asset.AssetType = STRING_TO_ASSET_TYPES_MAP[AssetTypeStr];
		}
		if (JsonObject->HasField(JSON_FIELD_ID))
		{
			Asset.Id = JsonObject->GetStringField(JSON_FIELD_ID);
		}
		if (JsonObject->HasTypedField<EJson::String>(JSON_FIELD_NAME))
		{
			Asset.Name = JsonObject->GetStringField(JSON_FIELD_NAME);
		}
		if (JsonObject->HasTypedField<EJson::String>(JSON_FIELD_GENDER))
		{
			Asset.Gender = FPayloadExtractor::GetGenderFromString(JsonObject->GetStringField(JSON_FIELD_GENDER));
		}
		if (JsonObject->HasTypedField<EJson::String>(JSON_FIELD_ICON_URL))
		{
			Asset.IconUrl = JsonObject->GetStringField(JSON_FIELD_ICON_URL);
		}
		if (JsonObject->HasTypedField<EJson::String>(JSON_FIELD_BADGE_LOGO_URL))
		{
			Asset.BadgeUrl = JsonObject->GetStringField(JSON_FIELD_BADGE_LOGO_URL);
		}
		if (JsonObject->HasTypedField<EJson::Boolean>(JSON_FIELD_IS_LOCKED))
		{
			Asset.bIsLocked = JsonObject->GetBoolField(JSON_FIELD_IS_LOCKED);
		}
		if (JsonObject->HasTypedField<EJson::String>(JSON_FIELD_PRICE))
		{
			Asset.Price = JsonObject->GetStringField(JSON_FIELD_PRICE);
		}
		if (JsonObject->HasTypedField<EJson::Array>(JSON_FIELD_IS_LOCKED_CATEGORIES))
		{
			Asset.bIsCustomizable = JsonObject->GetArrayField(JSON_FIELD_IS_LOCKED_CATEGORIES).Num() == 0;
		}
		PaginationData.Assets.Add(Asset);
	}
	TSharedPtr<FJsonObject> JsonObject;
	if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), JsonObject) && JsonObject->HasField(JSON_PAGINATION))
	{
		const TSharedPtr<FJsonObject> PaginationJson = JsonObject->GetObjectField(JSON_PAGINATION);
		PaginationData.TotalPages = PaginationJson->GetNumberField(JSON_TOTAL_PAGES);
		PaginationData.CurrentPage = PaginationJson->GetNumberField(JSON_PAGE);
		PaginationData.bHasNextPage = PaginationJson->GetBoolField(JSON_HAS_NEXT_PAGE);
	}
	return PaginationData;
}