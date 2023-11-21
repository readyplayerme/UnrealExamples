// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"

class FRpmUserAvatarDownloader : public TSharedFromThis<FRpmUserAvatarDownloader>
{
public:
	FRpmUserAvatarDownloader(TSharedPtr<class FRequestFactory> RequestFactory);

	void DownloadUserAvatars(const FUserAvatarsDownloadCompleted& DownloadCompleted, const FAvatarCreatorFailed& Failed);

	void AddAvatar(const FString& AvatarId, const FString& Partner);

	void DeleteAvatar(const FString& AvatarId);

private:
	void OnAvatarsDownloadCompleted(bool bSuccess);

	FUserAvatarsDownloadCompleted OnAvatarsDownloaded;
	FAvatarCreatorFailed OnFailed;

	TSharedPtr<class FRequestFactory> RequestFactory;
	TArray<FRpmUserAvatar> UserAvatars;
	TSharedPtr<class IBaseRequest> AvatarsRequest;
};
