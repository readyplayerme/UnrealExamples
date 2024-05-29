// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"

DECLARE_DELEGATE_OneParam(FFileDownloadCompleted, bool /*bSuccess*/);

class FAvatarRequest : public TSharedFromThis<FAvatarRequest>
{
public:
	void Download(const FString& Url, float Timeout = -1.f);

	void CancelRequest();

	FFileDownloadCompleted& GetCompleteCallback();

	const TArray<uint8>& GetContent() const;
	
	FString GetContentAsString() const;

private:
	void OnReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);

	FFileDownloadCompleted OnDownloadCompleted;

protected:
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> DownloadRequest;
};
