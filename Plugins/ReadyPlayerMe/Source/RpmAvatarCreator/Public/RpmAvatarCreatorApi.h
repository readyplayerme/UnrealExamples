// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"
#include "UObject/NoExportTypes.h"
#include "RpmAvatarCreatorApi.generated.h"

UCLASS(BlueprintType)
class RPMAVATARCREATOR_API URpmAvatarCreatorApi : public UObject
{
	GENERATED_BODY()

public:
	URpmAvatarCreatorApi();

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Initialize"))
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Set Preview Downloaded Delegate"))
	void SetPreviewDownloadedDelegate(const FPreviewDownloadCompleted& PreviewDownloaded);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Set Session Expired Delegate"))
	void SetSessionExpiredDelegate(const FSessionExpired& SessionExpired);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Get User Data"))
	FRpmUserData GetUserData() const;

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Authorize Anonymous"))
	void AuthAnonymous(const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Authorization Start"))
	void AuthStart(const FString& Email, bool bIsTypeCode, const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Confirm Activation Code"))
	void ConfirmActivationCode(const FString& Code, const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "LogOut"))
	void LogOut();

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Prepare Editor"))
	void PrepareEditor(const FAvatarEditorReady& EditorReady, const FAvatarCreatorFailed& Failed);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Update Avatar Asset"))
	void UpdateAvatarAsset(ERpmPartnerAssetType AssetType, const FString& AssetId);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Update Avatar Color"))
	void UpdateAvatarColor(ERpmPartnerAssetColor AssetColor, int32 ColorIndex);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Precompile Avatar"))
	void PrecompileAvatar(ERpmPartnerAssetType AssetType);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Download Avatar Templates"))
	void DownloadAvatarTemplates(const FAvatarTemplatesDownloadCompleted& DownloadCompleted, const FAvatarCreatorFailed& Failed);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Download User Avatars"))
	void DownloadUserAvatars(const FUserAvatarsDownloadCompleted& DownloadCompleted, const FAvatarCreatorFailed& Failed);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Save Avatar"))
	void SaveAvatar(const FAvatarSaveCompleted& AvatarSaveCompleted, const FAvatarCreatorFailed& Failed);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Delete Avatar", AutoCreateRefTerm = "AvatarDeleteCompleted,Failed"))
	void DeleteAvatar(const FString& AvatarId, bool bIsDraft, const FAvatarDeleteCompleted& AvatarDeleteCompleted, const FAvatarCreatorFailed& Failed);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Update Locked Assets", AutoCreateRefTerm = "UpdateLockedAssetsCompleted,Failed"))
	void UpdateLockedAssets(const FUpdateLockedAssetsCompleted& UpdateLockedAssetsCompleted, const FAvatarCreatorFailed& Failed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me", Meta = (ExposeOnSpawn="true"))
	class USkeleton* TargetSkeleton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	FRpmAvatarProperties AvatarProperties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	FString SelectedAvatarTemplateId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me", Meta = (ExposeOnSpawn="true"))
	EAvatarBodyType BodyType;

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Download Image"))
	void DownloadImage(const FString& Url, int32 Size, const FImageDownloadCompleted& DownloadCompleted);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Get Filtered Partner Assets"))
	TArray<FRpmPartnerAsset> GetFilteredPartnerAssets() const;

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Get Color Palettes"))
	TArray<FRpmColorPalette> GetColorPalettes() const;

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Get Avatar Templates"))
	TArray<FRpmAvatarTemplate> GetAvatarTemplates() const;

	virtual void BeginDestroy() override;

	void Reset();

private:
	UFUNCTION()
	void PropertiesDownloaded(bool bSuccess, ERpmAvatarCreatorError Error);

	UFUNCTION()
	void ExecuteEditorReadyCallback(bool bSuccess, ERpmAvatarCreatorError Error);

	TSharedPtr<class FRequestFactory> RequestFactory;
	TSharedPtr<class FRpmAuthManager> AuthManager;
	TSharedPtr<class FRpmColorDownloader> ColorDownloader;
	TSharedPtr<class FRpmPartnerAssetDownloader> AssetDownloader;
	TSharedPtr<class FRpmUserAvatarDownloader> UserAvatarDownloader;
	TSharedPtr<class FRpmAvatarTemplateDownloader> AvatarTemplateDownloader;

	UPROPERTY()
	class URpmImageDownloader* ImageDownloader;

	UPROPERTY()
	class URpmAvatarRequestHandler* AvatarRequestHandler;

	FAvatarEditorReady OnEditorReady;
	FAvatarCreatorFailed OnEditorFailed;
};
