// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"
#include "UObject/NoExportTypes.h"
#include "RpmAvatarRequestHandler.generated.h"

UCLASS()
class URpmAvatarRequestHandler : public UObject
{
	GENERATED_BODY()

public:
	URpmAvatarRequestHandler();

	void SetRequestFactory(TSharedPtr<class FRequestFactory> Factory);

	void SetUserAvatarDownloader(TSharedPtr<class FRpmUserAvatarDownloader> AvatarDownloader);

	void CreateAvatar(const FRpmAvatarProperties& Properties, const FString& TemplateId);

	void Precompile(ERpmPartnerAssetType AssetType, const TArray<FRpmPartnerAsset>& FilteredAssets);

	void UpdateAvatar(ERpmPartnerAssetType AssetType, const FString& AssetId);

	void UpdateAvatar(ERpmPartnerAssetColor AssetColor, int32 ColorIndex);

	void DownloadAvatarProperties(const FString& InAvatarId);

	void DownloadModel(class USkeleton* Skeleton);

	void SaveAvatar(const FAvatarSaveCompleted& AvatarSaveCompleted, const FAvatarCreatorFailed& Failed);

	void DeleteAvatar(const FString& AvatarId, bool bIsDraft, const FAvatarDeleteCompleted& AvatarDeleteCompleted, const FAvatarCreatorFailed& Failed);

	FRpmAvatarProperties GetAvatarProperties() const;

	UPROPERTY()
	USkeletalMesh* Mesh;

	UPROPERTY()
	class URpmImageDownloader* ImageDownloader;

	UPROPERTY()
	FPreviewDownloadCompleted OnPreviewDownloaded;

	FBaseRequestCompleted& GetAvatarPropertiesDownloadedCallback();

	FBaseRequestCompleted& GetAvatarPreviewDownloadedCallback();

	void Reset() const;

private:
	UFUNCTION()
	void OnUpdateAvatarCompleted(bool bSuccess);

	UFUNCTION()
	void OnSaveAvatarCompleted(bool bSuccess, FAvatarSaveCompleted AvatarSaveCompleted, FAvatarCreatorFailed Failed);

	UFUNCTION()
	void OnDeleteAvatarCompleted(bool bSuccess, FAvatarDeleteCompleted AvatarDeleteCompleted, FAvatarCreatorFailed Failed, FString AvatarId, bool bIsDraft);

	UFUNCTION()
	void OnModelDownloadCompleted(bool bSuccess);

	UFUNCTION()
	void OnPropertiesRequestCompleted(bool bSuccess);

	UFUNCTION()
	void OnPrecompileCompleted(bool bSuccess);

	void UpdateAvatar(const FString& Payload);

	void LoadGlb(const TArray<uint8>& Data);

	UPROPERTY()
	USkeleton* TargetSkeleton;

	bool bAvatarExists;
	bool bIsExistingAvatarUnchanged;

	FRpmAvatarProperties AvatarProperties;

	FBaseRequestCompleted OnAvatarPropertiesDownloaded;
	FBaseRequestCompleted OnAvatarPreviewDownloaded;

	TSharedPtr<class FRequestFactory> RequestFactory;
	TSharedPtr<class FRpmUserAvatarDownloader> UserAvatarDownloader;
	TSharedPtr<class IBaseRequest> AvatarMetadataRequest;
	TSharedPtr<class IBaseRequest> UpdateAvatarRequest;
	TSharedPtr<class IBaseRequest> SaveAvatarRequest;
	TSharedPtr<class IBaseRequest> DeleteAvatarRequest;
	TSharedPtr<class IBaseRequest> AvatarModelRequest;
	TSharedPtr<class IBaseRequest> PrecompileRequest;
};
