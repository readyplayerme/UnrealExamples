// Copyright © 2023++ Ready Player Me

#pragma once

#include "IBaseRequest.h"
#include "RpmAvatarCreatorTypes.h"

DECLARE_DELEGATE_TwoParams(FTokenRefreshed, const FString&, const FString&);

class FAuthorizedRequest : public IBaseRequest, public TSharedFromThis<FAuthorizedRequest>
{
public:
	FAuthorizedRequest() = default;
	FAuthorizedRequest(TSharedPtr<IBaseRequest> MainRequest, const TSharedPtr<IBaseRequest> RefreshRequest, const FTokenRefreshed& TokenRefreshedDelegate, const FSessionExpired& SessionExpired);

	virtual void Download() override;
	virtual void CancelRequest() override;

	virtual FFileDownloadCompleted& GetCompleteCallback() override;

	virtual FString GetContentAsString() const override;
	virtual const TArray<uint8>& GetContent() const override;
	virtual int32 GetResponseCode() const override;
	virtual void SetAuthToken(const FString& Token) override {}

private:
	void MainRequestCompleted(bool bSuccess);
	void RefreshRequestCompleted(bool bSuccess);

	void ExecuteRequestCompletedCallback(bool bSuccess);
	void ExecuteSessionExpiredCallback();

	FFileDownloadCompleted OnDownloadCompleted;

	TSharedPtr<IBaseRequest> MainRequest;
	TSharedPtr<IBaseRequest> TokenRefreshRequest;
	FTokenRefreshed TokenRefreshedDelegate;
	FSessionExpired SessionExpiredDelegate;
};
