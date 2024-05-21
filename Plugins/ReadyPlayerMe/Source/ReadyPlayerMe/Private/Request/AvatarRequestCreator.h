// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

class FAvatarRequestCreator
{
public:
	static auto MakeHttpRequest(const FString& Url, float Timeout = -1.f)
	{
		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
		if (Timeout > 0.f)
		{
			HttpRequest->SetTimeout(Timeout);
		}
		HttpRequest->SetURL(Url);
		return HttpRequest;
	}
};
