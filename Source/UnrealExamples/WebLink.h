// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WebLink.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FReadyPlayerWebBrowserResponse, const FString&, AvatarUrl);
UCLASS()
class UWebLink : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me")
	void AvatarGenerated(FString JsonResponse);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RPM Set Callback"), Category = "Ready Player Me")
	void SetAvatarUrlCallback(const FReadyPlayerWebBrowserResponse& WebBrowserCallback);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RPM Get Last Avatar Url"), Category = "Ready Player Me")
	FString GetLastAvatarUrl();

private:

	FReadyPlayerWebBrowserResponse WebBrowserResponse;
	FString LastAvatarUrl;
};
