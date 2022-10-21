// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Runtime/Launch/Resources/Version.h"

class FReadyPlayerMeRequestCreator
{
public:
	static auto MakeHttpRequest(const FString& Url, float Timeout = -1.f)
	{
#if ENGINE_MAJOR_VERSION > 4 || ENGINE_MINOR_VERSION > 25
		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
		if (Timeout > 0.f)
		{
			HttpRequest->SetTimeout(Timeout);
		}
#else
		TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
#endif
		HttpRequest->SetURL(Url);
		return HttpRequest;
	}
};
