// Copyright © 2023++ Ready Player Me


#include "RpmUserAvatarDownloader.h"

#include "Requests/RequestFactory.h"
#include "Extractors/UserAvatarExtractor.h"
#include "Requests/Endpoints.h"

FRpmUserAvatarDownloader::FRpmUserAvatarDownloader(TSharedPtr<class FRequestFactory> RequestFactory)
	: RequestFactory(RequestFactory)
{
}

void FRpmUserAvatarDownloader::DownloadUserAvatars(const FUserAvatarsDownloadCompleted& DownloadCompleted, const FAvatarCreatorFailed& Failed)
{
	OnAvatarsDownloaded = DownloadCompleted;
	OnFailed = Failed;
	if (UserAvatars.Num() != 0)
	{
		(void)OnAvatarsDownloaded.ExecuteIfBound(UserAvatars);
		OnFailed.Unbind();
		OnAvatarsDownloaded.Unbind();
	}
	else
	{
		AvatarsRequest = RequestFactory->CreateUserAvatarsRequest();
		AvatarsRequest->GetCompleteCallback().BindSP(AsShared(), &FRpmUserAvatarDownloader::OnAvatarsDownloadCompleted);
		AvatarsRequest->Download();
	}
}

void FRpmUserAvatarDownloader::OnAvatarsDownloadCompleted(bool bSuccess)
{
	if (!bSuccess)
	{
		(void)OnFailed.ExecuteIfBound(ERpmAvatarCreatorError::UserAvatarDownloadFailure);
		OnFailed.Unbind();
		OnAvatarsDownloaded.Unbind();
		return;
	}
	UserAvatars = FUserAvatarExtractor::ExtractUserAvatars(AvatarsRequest->GetContentAsString());
	AvatarsRequest.Reset();
	(void)OnAvatarsDownloaded.ExecuteIfBound(UserAvatars);
	OnFailed.Unbind();
	OnAvatarsDownloaded.Unbind();
}

void FRpmUserAvatarDownloader::AddAvatar(const FString& AvatarId, const FString& Partner)
{
	FRpmUserAvatar UserAvatar;
	UserAvatar.Id = AvatarId;
	UserAvatar.Partner = Partner;
	UserAvatar.ImageUrl = FEndpoints::GetRenderEndpoint(UserAvatar.Id);
	UserAvatars.Add(UserAvatar);
}

void FRpmUserAvatarDownloader::DeleteAvatar(const FString& AvatarId)
{
	UserAvatars.RemoveAll([AvatarId](const auto& UserAvatar)
	{
		return UserAvatar.Id == AvatarId;
	});
}
