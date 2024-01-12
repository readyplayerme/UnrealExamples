// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"
#include "Blueprint/UserWidget.h"
#include "RpmAssetButtonUI.h"
#include "RpmColorButtonUI.h"
#include "RpmTemplateButtonUI.h"
#include "RpmAvatarEditorUI.generated.h"

UCLASS(Abstract)
class RPMAVATARCREATOR_API URpmAvatarEditorUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Init"))
	void Init(class URpmAvatarCreatorApi* Api);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Setup Templates"))
	void SetupTemplates();

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Setup Assets"))
	void SetupAssets();

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Discard Avatar Draft"))
	void DiscardAvatarDraft();

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Update Locked Assets"))
	void UpdateLockedAssets();

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "DownloadAssetIcons"))
	void DownloadAssetIcons(const class UWrapBox* AssetContainer);

	UFUNCTION(BlueprintImplementableEvent, Category = "Ready Player Me", meta = (DisplayName = "Asset Selected"))
	void AssetSelected(const FRpmPartnerAsset& Asset);

	UFUNCTION(BlueprintImplementableEvent, Category = "Ready Player Me", meta = (DisplayName = "Color Selected"))
	void ColorSelected();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ready Player Me", meta = (DisplayName = "Template Selected"))
	void TemplateSelected(const FRpmAvatarTemplate& Template);

	UFUNCTION(BlueprintImplementableEvent, Category = "Ready Player Me", meta = (DisplayName = "Preview Downloaded"))
	void PreviewDownloaded(const USkeletalMesh* SkeletalMesh);

	UFUNCTION(BlueprintImplementableEvent, Category = "Ready Player Me", meta = (DisplayName = "Asset Unlocked"))
	void AssetUnlocked();

	UFUNCTION(BlueprintPure, Category = "Ready Player Me", meta = (DisplayName = "Is Customizable Asset Selected"))
	bool IsCustomizableAssetSelected() const;

	UFUNCTION(BlueprintPure, Category = "Ready Player Me", meta = (DisplayName = "Are Modular Outfits Disabled"))
	bool AreModularOutfitsDisabled() const;

	UPROPERTY(BlueprintReadWrite, Category="Ready Player Me")
	TMap<ERpmPartnerAssetType, UWrapBox*> AssetContainerMap;

	UPROPERTY(BlueprintReadWrite, Category="Ready Player Me")
	TMap<ERpmPartnerAssetColor, UWrapBox*> ColorContainerMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	UWrapBox* TemplateContainer = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	TSubclassOf<URpmAssetButtonUI> AssetButtonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	TSubclassOf<URpmAssetButtonUI> EyeColorButtonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	TSubclassOf<URpmColorButtonUI> ColorButtonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	TSubclassOf<URpmTemplateButtonUI> TemplateButtonClass;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category="Ready Player Me")
	class URpmIconUI* BadgeIcon = nullptr;

	UPROPERTY(BlueprintReadWrite, Category="Ready Player Me")
	class URpmAvatarCreatorApi* AvatarCreatorApi = nullptr;

private:
	UWrapBox* GetColorContainerByColor(ERpmPartnerAssetColor Color) const;

	UWrapBox* GetAssetContainerByAsset(ERpmPartnerAssetType AssetType) const;

	void ClearContainers();

	void AddClearSelectionButtons();

	void AddAssetButtons();

	void AddAssetButton(const FRpmPartnerAsset& Asset, UWrapBox* WrapBox);

	void AddColorButtons();

	bool IsAssetSelected(const FRpmPartnerAsset& Asset) const;

	void SetAssetSelectedPin(const FRpmPartnerAsset& Asset);

	void RemoveAssetSelectedPin(ERpmPartnerAssetType AssetType);

	void SetColorSelectedPin(ERpmPartnerAssetColor AssetColor, int32 ColorIndex);

	UFUNCTION()
	void OnAssetIconDownloaded(UTexture2D* Image, const FString& Url);

	UFUNCTION()
	void OnTemplateIconDownloaded(UTexture2D* Image, const FString& Url);

	UFUNCTION()
	void OnBadgeIconDownloaded(UTexture2D* Image, const FString& Url);

	UFUNCTION()
	void OnUpdateLockedAssetsCompleted();

	UFUNCTION()
	void OnAssetButtonClicked(const FRpmPartnerAsset& Asset);

	UFUNCTION()
	void OnColorButtonClicked(ERpmPartnerAssetColor AssetColor, int32 ColorIndex);

	UFUNCTION()
	void OnTemplateButtonClicked(const FRpmAvatarTemplate& Template);

	UPROPERTY()
	FImageDownloadCompleted AssetIconDownloadCompleted;

	UPROPERTY()
	FImageDownloadCompleted TemplateIconDownloadCompleted;

	UPROPERTY()
	FImageDownloadCompleted BadgeIconDownloadCompleted;

	UPROPERTY()
	FUpdateLockedAssetsCompleted UpdateLockedAssetsCompleted;

	UPROPERTY()
	TMap<FString, URpmAssetButtonUI*> AssetImageMap;

	UPROPERTY()
	TMap<FString, URpmTemplateButtonUI*> TemplateImageMap;

	bool bIsCustomizableAssetSelected = true;
	bool bAreModularOutfitsDisabled = false;
};
