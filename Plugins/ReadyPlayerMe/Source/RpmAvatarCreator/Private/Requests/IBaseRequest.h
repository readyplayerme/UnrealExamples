// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"

enum class ERequestVerb
{
	Get,
	Post,
	Put,
	Patch,
	Delete
};

DECLARE_DELEGATE_OneParam(FFileDownloadCompleted, bool /*bSuccess*/);
DECLARE_MULTICAST_DELEGATE(FCancellationDelegate);

class IBaseRequest
{
public:
	virtual ~IBaseRequest() = default;

	virtual void Download() = 0;
	virtual void CancelRequest() = 0;

	virtual FFileDownloadCompleted& GetCompleteCallback() = 0;

	virtual FString GetContentAsString() const = 0;
	virtual const TArray<uint8>& GetContent() const = 0;
	virtual int32 GetResponseCode() const = 0;
	virtual void SetAuthToken(const FString& Token) = 0;
};
