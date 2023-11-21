// Copyright © 2023++ Ready Player Me


#include "AuthorizedRequest.h"

#include "Interfaces/IHttpResponse.h"
#include "Extractors/UserDataExtractor.h"

FAuthorizedRequest::FAuthorizedRequest(TSharedPtr<IBaseRequest> MainRequest, const TSharedPtr<IBaseRequest> RefreshRequest, const FTokenRefreshed& TokenRefreshedDelegate, const FSessionExpired& SessionExpired)
			: MainRequest(MainRequest)
			, TokenRefreshRequest(RefreshRequest)
			, TokenRefreshedDelegate(TokenRefreshedDelegate)
			, SessionExpiredDelegate(SessionExpired)
{
}

void FAuthorizedRequest::MainRequestCompleted(bool bSuccess)
{
	if (!bSuccess && MainRequest->GetResponseCode() == EHttpResponseCodes::Denied && TokenRefreshedDelegate.IsBound())
	{
		if (TokenRefreshRequest.IsValid())
		{
			TokenRefreshRequest->GetCompleteCallback().BindSP(AsShared(), &FAuthorizedRequest::RefreshRequestCompleted);
			TokenRefreshRequest->Download();
		}
		else
		{
			ExecuteSessionExpiredCallback();
		}
	}
	else
	{
		ExecuteRequestCompletedCallback(bSuccess);
	}
}

void FAuthorizedRequest::ExecuteRequestCompletedCallback(bool bSuccess)
{
	(void)OnDownloadCompleted.ExecuteIfBound(bSuccess);
	OnDownloadCompleted.Unbind();
	TokenRefreshRequest.Reset();
}

void FAuthorizedRequest::ExecuteSessionExpiredCallback()
{
	(void)SessionExpiredDelegate.ExecuteIfBound();
	MainRequest.Reset();
	OnDownloadCompleted.Unbind();
	TokenRefreshRequest.Reset();
}

void FAuthorizedRequest::RefreshRequestCompleted(bool bSuccess)
{
	if (bSuccess)
	{
		const auto UserData = FUserDataExtractor::ExtractRefreshedUserSession(TokenRefreshRequest->GetContentAsString());
		if (UserData.bIsAuthenticated)
		{
			(void)TokenRefreshedDelegate.ExecuteIfBound(UserData.Token, UserData.RefreshToken);
			TokenRefreshRequest.Reset();
			MainRequest->SetAuthToken(UserData.Token);
			Download();
			return;
		}
	}
	else if ((TokenRefreshRequest->GetResponseCode() == EHttpResponseCodes::Denied || TokenRefreshRequest->GetResponseCode() == EHttpResponseCodes::BadRequest) && SessionExpiredDelegate.IsBound())
	{
		ExecuteSessionExpiredCallback();
		return;
	}
	ExecuteRequestCompletedCallback(false);
}

FFileDownloadCompleted& FAuthorizedRequest::GetCompleteCallback()
{
	return OnDownloadCompleted;
}

void FAuthorizedRequest::Download()
{
	MainRequest->GetCompleteCallback().BindSP(AsShared(), &FAuthorizedRequest::MainRequestCompleted);
	MainRequest->Download();
}

void FAuthorizedRequest::CancelRequest()
{
	MainRequest->CancelRequest();
	if (TokenRefreshRequest)
	{
		TokenRefreshRequest->CancelRequest();
	}
}

FString FAuthorizedRequest::GetContentAsString() const
{
	return MainRequest->GetContentAsString();
}

const TArray<uint8>& FAuthorizedRequest::GetContent() const
{
	return MainRequest->GetContent();
}

int32 FAuthorizedRequest::GetResponseCode() const
{
	return MainRequest->GetResponseCode();
}