// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WebLink.generated.h"

UCLASS()
class UWebLink : public UObject
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me")
	void EventReceived(FString JsonResponse);

	// Setter for UReadyPlayerMeWebBrowser reference
	void SetWebBrowser(class UReadyPlayerMeWebBrowser& InWebBrowser)
	{
		WebBrowser = &InWebBrowser;
	}
	
private:
	// Reference to UReadyPlayerMeWebBrowser
	UReadyPlayerMeWebBrowser* WebBrowser;
};
