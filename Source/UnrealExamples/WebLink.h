// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "WebLink.generated.h"

UCLASS()
class UWebLink : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me|Web Browser")
	void EventReceived(const FString JsonResponse);

	void SetWebBrowser(class UReadyPlayerMeWebBrowser& InWebBrowser)
	{
		WebBrowser = &InWebBrowser;
	}

private:
	UReadyPlayerMeWebBrowser* WebBrowser;
};
