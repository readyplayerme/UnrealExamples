// Copyright © 2023++ Ready Player Me

#include "UI/RpmAvatarEditorUI.h"
#include "RpmAvatarCreatorApi.h"
#include "Blueprint/WidgetTree.h"
#include "Components/WrapBox.h"

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
	AssetButton->SetSelected(IsAssetSelected(Asset));
	AssetButton->Asset = Asset;
	AssetButton->AvatarCreatorApi = AvatarCreatorApi;
	AssetButton->UpdateUI();
	WrapBox->AddChildToWrapBox(AssetButton);
	AssetButton->AssetButtonSelected.AddDynamic(this, &URpmAvatarEditorUI::OnAssetButtonClicked);
}

void URpmAvatarEditorUI::OnAssetButtonClicked(const FRpmPartnerAsset& Asset)
{
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
}

bool URpmAvatarEditorUI::IsAssetSelected(const FRpmPartnerAsset& Asset) const
{
	if (AvatarCreatorApi->AvatarProperties.Assets.Contains(Asset.AssetType))
	{
		return AvatarCreatorApi->AvatarProperties.Assets[Asset.AssetType] == Asset.Id;
	}
	return Asset.Id == 0;
}

void URpmAvatarEditorUI::SetAssetSelectedPin(const FRpmPartnerAsset& Asset)
{
	const UWrapBox* AssetContainer = GetAssetContainerByAsset(Asset.AssetType);
	for (UWidget* Widget : AssetContainer->GetAllChildren())
	{
		URpmAssetButtonUI* AssetButton = Cast<URpmAssetButtonUI>(Widget);
		const bool IsSelected = AssetButton->Asset.Id == Asset.Id && AssetButton->Asset.AssetType == Asset.AssetType;
		AssetButton->SetSelected(IsSelected);
	}
}

void URpmAvatarEditorUI::RemoveAssetSelectedPin(ERpmPartnerAssetType AssetType)
{
	const UWrapBox* AssetContainer = GetAssetContainerByAsset(AssetType);
	for (UWidget* Widget : AssetContainer->GetAllChildren())
	{
		URpmAssetButtonUI* AssetButton = Cast<URpmAssetButtonUI>(Widget);
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
