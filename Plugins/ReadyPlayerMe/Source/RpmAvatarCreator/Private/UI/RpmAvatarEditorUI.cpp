// Copyright © 2023++ Ready Player Me

#include "UI/RpmAvatarEditorUI.h"
#include "RpmAvatarCreatorApi.h"
#include "Blueprint/WidgetTree.h"
#include "Components/WrapBox.h"
#include "UI/RpmBadgeIconUI.h"

static const TSet<ERpmPartnerAssetType> EXCLUDE_CLEAR_SELECTION_ASSETS =
{
	ERpmPartnerAssetType::EyeColor,
	ERpmPartnerAssetType::Shirt,
	ERpmPartnerAssetType::Outfit,
	ERpmPartnerAssetType::Top,
	ERpmPartnerAssetType::Bottom,
	ERpmPartnerAssetType::Footwear
};

void URpmAvatarEditorUI::Init(class URpmAvatarCreatorApi* Api)
{
	AvatarCreatorApi = Api;
	FPreviewDownloadCompleted PreviewDownloadedDelegate;
	PreviewDownloadedDelegate.BindDynamic(this, &URpmAvatarEditorUI::PreviewDownloaded);
	AvatarCreatorApi->SetPreviewDownloadedDelegate(PreviewDownloadedDelegate);
	AssetIconDownloadCompleted.BindDynamic(this, &URpmAvatarEditorUI::OnAssetIconDownloaded);
	TemplateIconDownloadCompleted.BindDynamic(this, &URpmAvatarEditorUI::OnTemplateIconDownloaded);
	BadgeIconDownloadCompleted.BindDynamic(this, &URpmAvatarEditorUI::OnBadgeIconDownloaded);
}

void URpmAvatarEditorUI::SetupAssets()
{
	ClearContainers();
	AddClearSelectionButtons();
	AddAssetButtons();
	AddColorButtons();
	bAreModularOutfitsDisabled = AssetContainerMap[ERpmPartnerAssetType::Top]->GetChildrenCount() == 0 ||
		AssetContainerMap[ERpmPartnerAssetType::Bottom]->GetChildrenCount() == 0 ||
		AssetContainerMap[ERpmPartnerAssetType::Footwear]->GetChildrenCount() == 0;
}

void URpmAvatarEditorUI::DiscardAvatarDraft()
{
	auto& AvatarProperties = AvatarCreatorApi->AvatarProperties;
	if (!AvatarProperties.Id.IsEmpty())
	{
		AvatarCreatorApi->DeleteAvatar(AvatarProperties.Id, true, {}, {});
	}
	AvatarCreatorApi->SelectedAvatarTemplateId.Empty();
	AvatarProperties.Assets.Empty();
	AvatarProperties.Colors.Empty();
	AvatarProperties.Id.Empty();
	AvatarProperties.Base64Image.Empty();
	AvatarCreatorApi->Reset();
}

void URpmAvatarEditorUI::UpdateLockedAssets()
{
	AvatarCreatorApi->UpdateLockedAssets(UpdateLockedAssetsCompleted, {});
}

void URpmAvatarEditorUI::OnUpdateLockedAssetsCompleted()
{
	bool ContainsLockedAsset = false;
	const auto& SelectedAssets = AvatarCreatorApi->AvatarProperties.Assets;
	for (const auto& Asset : AvatarCreatorApi->GetFilteredPartnerAssets())
	{
		if (SelectedAssets.Contains(Asset.AssetType) && SelectedAssets[Asset.AssetType].Equals(Asset.Id) && Asset.bIsLocked)
		{
			ContainsLockedAsset = true;
			break;
		}
	}
	if (!ContainsLockedAsset)
	{
		AssetUnlocked();
	}
}

bool URpmAvatarEditorUI::IsCustomizableAssetSelected() const
{
	return bIsCustomizableAssetSelected;
}

bool URpmAvatarEditorUI::AreModularOutfitsDisabled() const
{
	return bAreModularOutfitsDisabled;
}

UWrapBox* URpmAvatarEditorUI::GetColorContainerByColor(ERpmPartnerAssetColor Color) const
{
	return ColorContainerMap[Color];
}

UWrapBox* URpmAvatarEditorUI::GetAssetContainerByAsset(ERpmPartnerAssetType AssetType) const
{
	return AssetContainerMap[AssetType];
}

void URpmAvatarEditorUI::ClearContainers()
{
	for (const auto Pair : ColorContainerMap)
	{
		Pair.Value->ClearChildren();
	}
	for (const auto Pair : AssetContainerMap)
	{
		Pair.Value->ClearChildren();
	}
}

void URpmAvatarEditorUI::AddClearSelectionButtons()
{
	for (const auto Pair : AssetContainerMap)
	{
		if (!EXCLUDE_CLEAR_SELECTION_ASSETS.Contains(Pair.Key))
		{
			FRpmPartnerAsset Asset;
			Asset.AssetType = Pair.Key;
			AddAssetButton(Asset, Pair.Value);
		}
	}
}

void URpmAvatarEditorUI::AddAssetButtons()
{
	bIsCustomizableAssetSelected = true;
	const TArray<FRpmPartnerAsset> AllAssets = AvatarCreatorApi->GetFilteredPartnerAssets();
	for (const auto Pair : AssetContainerMap)
	{
		for (const FRpmPartnerAsset& Asset : AllAssets)
		{
			if (Asset.AssetType == Pair.Key)
			{
				AddAssetButton(Asset, Pair.Value);
				if (IsAssetSelected(Asset) && !Asset.bIsCustomizable)
				{
					bIsCustomizableAssetSelected = false;
				}
			}
		}
	}
}

void URpmAvatarEditorUI::AddAssetButton(const FRpmPartnerAsset& Asset, UWrapBox* WrapBox)
{
	const auto& ButtonClass = Asset.AssetType == ERpmPartnerAssetType::EyeColor ? EyeColorButtonClass : AssetButtonClass;
	URpmAssetButtonUI* AssetButton = WidgetTree->ConstructWidget<URpmAssetButtonUI>(ButtonClass);
	AssetButton->bIsSelected = IsAssetSelected(Asset);
	AssetButton->SetSelected(AssetButton->bIsSelected);
	AssetButton->Asset = Asset;
	AssetButton->UpdateUI();
	WrapBox->AddChildToWrapBox(AssetButton);
	AssetButton->AssetButtonSelected.AddDynamic(this, &URpmAvatarEditorUI::OnAssetButtonClicked);
}

void URpmAvatarEditorUI::OnAssetButtonClicked(const FRpmPartnerAsset& Asset)
{
	if (AvatarCreatorApi->AvatarProperties.Assets.Contains(Asset.AssetType) && AvatarCreatorApi->AvatarProperties.Assets[Asset.AssetType] == Asset.Id)
	{
		return;
	}
	AssetSelected(Asset);
	AvatarCreatorApi->UpdateAvatarAsset(Asset.AssetType, Asset.Id);
	SetAssetSelectedPin(Asset);
	if (!bAreModularOutfitsDisabled)
	{
		if (Asset.AssetType == ERpmPartnerAssetType::Outfit)
		{
			RemoveAssetSelectedPin(ERpmPartnerAssetType::Top);
			RemoveAssetSelectedPin(ERpmPartnerAssetType::Bottom);
			RemoveAssetSelectedPin(ERpmPartnerAssetType::Footwear);
		}
		else if (Asset.AssetType == ERpmPartnerAssetType::Top || Asset.AssetType == ERpmPartnerAssetType::Bottom || Asset.AssetType == ERpmPartnerAssetType::Footwear)
		{
			RemoveAssetSelectedPin(ERpmPartnerAssetType::Outfit);
		}
	}
	if (BadgeIcon)
	{
		if (Asset.BadgeUrl.IsEmpty())
		{
			BadgeIcon->SetIconTexture(nullptr);
		}
		else
		{
			AvatarCreatorApi->DownloadImage(Asset.BadgeUrl, BadgeIcon->IconSize, BadgeIconDownloadCompleted);
		}
	}
}

bool URpmAvatarEditorUI::IsAssetSelected(const FRpmPartnerAsset& Asset) const
{
	if (AvatarCreatorApi->AvatarProperties.Assets.Contains(Asset.AssetType))
	{
		return AvatarCreatorApi->AvatarProperties.Assets[Asset.AssetType] == Asset.Id;
	}
	return Asset.Id == "0";
}

void URpmAvatarEditorUI::SetAssetSelectedPin(const FRpmPartnerAsset& Asset)
{
	const UWrapBox* AssetContainer = GetAssetContainerByAsset(Asset.AssetType);
	for (UWidget* Widget : AssetContainer->GetAllChildren())
	{
		URpmAssetButtonUI* AssetButton = Cast<URpmAssetButtonUI>(Widget);
		AssetButton->bIsSelected = AssetButton->Asset.Id == Asset.Id && AssetButton->Asset.AssetType == Asset.AssetType;
		AssetButton->SetSelected(AssetButton->bIsSelected);
	}
}

void URpmAvatarEditorUI::RemoveAssetSelectedPin(ERpmPartnerAssetType AssetType)
{
	const UWrapBox* AssetContainer = GetAssetContainerByAsset(AssetType);
	for (UWidget* Widget : AssetContainer->GetAllChildren())
	{
		URpmAssetButtonUI* AssetButton = Cast<URpmAssetButtonUI>(Widget);
		AssetButton->bIsSelected = false;
		AssetButton->SetSelected(false);
	}
}

void URpmAvatarEditorUI::AddColorButtons()
{
	const TArray<FRpmColorPalette>& ColorPalettes = AvatarCreatorApi->GetColorPalettes();
	for (const FRpmColorPalette& ColorPalette : ColorPalettes)
	{
		UWrapBox* ColorContainer = GetColorContainerByColor(ColorPalette.AssetColor);
		for (int i = 0; i < ColorPalette.RgbColors.Num(); ++i)
		{
			const FColor RgbColor = ColorPalette.RgbColors[i];
			URpmColorButtonUI* ColorButton = WidgetTree->ConstructWidget<URpmColorButtonUI>(ColorButtonClass);
			const bool IsSelected = AvatarCreatorApi->AvatarProperties.Colors[ColorPalette.AssetColor] == i;
			ColorButton->SetSelected(IsSelected);
			ColorButton->AssetColor = ColorPalette.AssetColor;
			ColorButton->RgbColor = RgbColor;
			ColorButton->ColorIndex = i;
			ColorButton->UpdateUI();
			ColorContainer->AddChildToWrapBox(ColorButton);
			ColorButton->ColorButtonSelected.AddDynamic(this, &URpmAvatarEditorUI::OnColorButtonClicked);
		}
	}
}

void URpmAvatarEditorUI::OnColorButtonClicked(ERpmPartnerAssetColor AssetColor, int32 ColorIndex)
{
	ColorSelected();
	AvatarCreatorApi->UpdateAvatarColor(AssetColor, ColorIndex);
	SetColorSelectedPin(AssetColor, ColorIndex);
}

void URpmAvatarEditorUI::SetColorSelectedPin(ERpmPartnerAssetColor AssetColor, int32 ColorIndex)
{
	const UWrapBox* AssetContainer = GetColorContainerByColor(AssetColor);
	for (UWidget* Widget : AssetContainer->GetAllChildren())
	{
		URpmColorButtonUI* ColorButton = Cast<URpmColorButtonUI>(Widget);
		const bool IsSelected = ColorButton->AssetColor == AssetColor && ColorButton->ColorIndex == ColorIndex;
		ColorButton->SetSelected(IsSelected);
	}
}

void URpmAvatarEditorUI::DownloadAssetIcons(const UWrapBox* AssetContainer)
{
	for (UWidget* Widget : AssetContainer->GetAllChildren())
	{
		URpmAssetButtonUI* AssetButton = Cast<URpmAssetButtonUI>(Widget);
		const FString& IconUrl = AssetButton->Asset.IconUrl;
		if (!IconUrl.IsEmpty())
		{
			AssetImageMap.Add(IconUrl, AssetButton);
			AvatarCreatorApi->DownloadImage(IconUrl, AssetButton->IconSize, AssetIconDownloadCompleted);
		}
	}
}

void URpmAvatarEditorUI::OnAssetIconDownloaded(UTexture2D* Image, const FString& Url)
{
	if (AssetImageMap.Contains(Url))
	{
		AssetImageMap[Url]->SetIconTexture(Image);
		AssetImageMap.Remove(Url);
	}
}

void URpmAvatarEditorUI::SetupTemplates()
{
	TemplateContainer->ClearChildren();
	for (const FRpmAvatarTemplate& Template : AvatarCreatorApi->GetAvatarTemplates())
	{
		if (Template.Gender != AvatarCreatorApi->AvatarProperties.Gender)
		{
			continue;
		}
		URpmTemplateButtonUI* TemplateButton = WidgetTree->ConstructWidget<URpmTemplateButtonUI>(TemplateButtonClass);
		TemplateButton->Template = Template;
		TemplateButton->UpdateUI();
		TemplateContainer->AddChildToWrapBox(TemplateButton);
		TemplateButton->TemplateButtonSelected.AddDynamic(this, &URpmAvatarEditorUI::OnTemplateButtonClicked);

		TemplateImageMap.Add(Template.ImageUrl, TemplateButton);
		AvatarCreatorApi->DownloadImage(Template.ImageUrl, TemplateButton->IconSize, TemplateIconDownloadCompleted);
	}
}

void URpmAvatarEditorUI::OnTemplateButtonClicked(const FRpmAvatarTemplate& Template)
{
	AvatarCreatorApi->SelectedAvatarTemplateId = Template.Id;
	TemplateSelected(Template);
	for (UWidget* Widget : TemplateContainer->GetAllChildren())
	{
		URpmTemplateButtonUI* TemplateButton = Cast<URpmTemplateButtonUI>(Widget);
		const bool IsSelected = TemplateButton->Template.Id == Template.Id;
		TemplateButton->SetSelected(IsSelected);
	}
}

void URpmAvatarEditorUI::OnTemplateIconDownloaded(UTexture2D* Image, const FString& Url)
{
	if (TemplateImageMap.Contains(Url))
	{
		TemplateImageMap[Url]->SetIconTexture(Image);
		TemplateImageMap.Remove(Url);
	}
}

void URpmAvatarEditorUI::OnBadgeIconDownloaded(UTexture2D* Image, const FString& Url)
{
	BadgeIcon->SetIconTexture(Image);
}
