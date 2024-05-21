// Copyright © 2024 Ready Player Me


#include "AvatarRequest.h"

#include "ReadyPlayerMeSettings.h"
#include "AvatarRequestCreator.h"
#include "Utils/PluginInfo.h"

static const FString HEADER_RPM_SOURCE = "RPM-Source";
static const FString HEADER_RPM_SDK_VERSION = "RPM-SDK-Version";
static const FString HEADER_APP_ID = "X-APP-ID";
#if WITH_EDITOR
static const FString UNREAL_SOURCE = "unreal-editor";
#else
static const FString UNREAL_SOURCE = "unreal-runtime";
#endif

namespace
{
	template <typename RequestPtr>
	void AddRPMHeaders(RequestPtr HttpRequest)
	{
		const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
		if (Settings)
		{
			HttpRequest->SetHeader(HEADER_APP_ID, Settings->AppId);
		}
		HttpRequest->SetHeader(HEADER_RPM_SOURCE, UNREAL_SOURCE);
		HttpRequest->SetHeader(HEADER_RPM_SDK_VERSION, FPluginInfo::GetRpmPluginVersion());
	}
}

void FAvatarRequest::Download(const FString& Url, float Timeout)
{
	DownloadRequest = FAvatarRequestCreator::MakeHttpRequest(Url, Timeout);
	DownloadRequest->OnProcessRequestComplete().BindSP(this, &FAvatarRequest::OnReceived);
	AddRPMHeaders(DownloadRequest);
	DownloadRequest->ProcessRequest();
}

FFileDownloadCompleted& FAvatarRequest::GetCompleteCallback()
{
	return OnDownloadCompleted;
}

void FAvatarRequest::CancelRequest()
{
	if (DownloadRequest.IsValid() && (DownloadRequest->GetStatus() == EHttpRequestStatus::Type::Processing || DownloadRequest->GetStatus() == EHttpRequestStatus::Type::NotStarted))
	{
		DownloadRequest->CancelRequest();
	}
	OnDownloadCompleted.Unbind();
}

void FAvatarRequest::OnReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	const bool Success = bSuccess && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode());
	(void)OnDownloadCompleted.ExecuteIfBound(Success);
	OnDownloadCompleted.Unbind();
}

const TArray<uint8>& FAvatarRequest::GetContent() const
{
	return DownloadRequest->GetResponse()->GetContent();
}

FString FAvatarRequest::GetContentAsString() const
{
	return DownloadRequest->GetResponse()->GetContentAsString();
}
