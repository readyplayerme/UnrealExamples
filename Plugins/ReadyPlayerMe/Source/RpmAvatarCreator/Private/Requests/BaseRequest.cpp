// Copyright © 2023++ Ready Player Me


#include "BaseRequest.h"

#include "HttpModule.h"
#include "ReadyPlayerMeSettings.h"
#include "Interfaces/IHttpResponse.h"

namespace
{
	TMap<ERequestVerb, FString> REQUEST_VERB_MAP =
	{
		{ERequestVerb::Get, "GET"},
		{ERequestVerb::Post, "POST"},
		{ERequestVerb::Put, "PUT"},
		{ERequestVerb::Patch, "PATCH"},
		{ERequestVerb::Delete, "DELETE"}
	};

	const FString HEADER_AUTHORIZATION = "Authorization";
	const FString HEADER_APP_ID = "X-APP-ID";
	const FString HEADER_CONTENT_TYPE = "Content-Type";
	const FString HEADER_RPM_SOURCE = "rpm-source";
}

FBaseRequest::FBaseRequest(const TSharedRef<FCancellationDelegate>& CancellationDelegate, const FString& Url, const FString& AuthToken, ERequestVerb RequestVerb, const FString& Payload, float Timeout)
	: CancellationDelegate(CancellationDelegate)
	, Url(Url)
	, AuthToken(AuthToken)
	, RequestVerb(RequestVerb)
	, Payload(Payload)
	, Timeout(Timeout)
{
}

void FBaseRequest::Download()
{
	CancellationHandle = CancellationDelegate->AddSP(AsShared(), &FBaseRequest::CancelRequest);
	DownloadRequest = FHttpModule::Get().CreateRequest();
	if (Timeout > 0.f)
	{
		DownloadRequest->SetTimeout(Timeout);
	}
	DownloadRequest->SetHeader(HEADER_RPM_SOURCE, "unreal");
	DownloadRequest->SetURL(Url);
	if (!AuthToken.IsEmpty())
	{
		const FString Authorization = FString::Printf(TEXT("Bearer %s"), *AuthToken);
		DownloadRequest->SetHeader(HEADER_AUTHORIZATION, Authorization);
	}
	const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
	if (IsValid(Settings))
	{
		DownloadRequest->SetHeader(HEADER_APP_ID, Settings->AppId);
	}
	if (!Payload.IsEmpty())
	{
		DownloadRequest->SetHeader(HEADER_CONTENT_TYPE, "application/json");
		DownloadRequest->SetContentAsString(Payload);
	}
	DownloadRequest->OnProcessRequestComplete().BindSP(AsShared(), &FBaseRequest::OnReceived);
	DownloadRequest->SetVerb(REQUEST_VERB_MAP[RequestVerb]);
	DownloadRequest->ProcessRequest();
}

FFileDownloadCompleted& FBaseRequest::GetCompleteCallback()
{
	return OnDownloadCompleted;
}

void FBaseRequest::CancelRequest()
{
	if (DownloadRequest.IsValid() && (DownloadRequest->GetStatus() == EHttpRequestStatus::Type::Processing || DownloadRequest->GetStatus() == EHttpRequestStatus::Type::NotStarted))
	{
		DownloadRequest->CancelRequest();
	}
	OnDownloadCompleted.Unbind();
	CancellationDelegate->Remove(CancellationHandle);
}

void FBaseRequest::OnReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	const bool Success = bSuccess && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode());
	(void)OnDownloadCompleted.ExecuteIfBound(Success);
	OnDownloadCompleted.Unbind();
	CancellationDelegate->Remove(CancellationHandle);
}

FString FBaseRequest::GetContentAsString() const
{
	return DownloadRequest->GetResponse()->GetContentAsString();
}

const TArray<uint8>& FBaseRequest::GetContent() const
{
	return DownloadRequest->GetResponse()->GetContent();
}

int32 FBaseRequest::GetResponseCode() const
{
	return DownloadRequest->GetResponse()->GetResponseCode();
}

void FBaseRequest::SetAuthToken(const FString& Token)
{
	AuthToken = Token;
}
