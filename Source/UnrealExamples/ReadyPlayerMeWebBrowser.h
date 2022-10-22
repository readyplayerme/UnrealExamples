// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "WebBrowser.h"
#include "WebLink.h"
#include "SWebBrowser.h"
#include "ReadyPlayerMeWebBrowser.generated.h"

UENUM(BlueprintType)
enum class ESelectBodyType : uint8
{
	None,
	Select,
	FullBody,
	HalfBody,
};

UENUM(BlueprintType)
enum class ESelectGender : uint8
{
	None,
	Male,
	Female,
};

/**
 * 
 */
UCLASS()
class UReadyPlayerMeWebBrowser : public UWebBrowser
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Setup Browser"), Category = "Ready Player Me|Web Browser")
	void SetupBrowser(const FReadyPlayerWebBrowserResponse& Response);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Bind Browser To Object"), Category = "Ready Player Me|Web Browser")
	void BindBrowserToObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	bool bClearCache = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	ESelectBodyType SelectBodyType = ESelectBodyType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	ESelectGender SelectGender = ESelectGender::None;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	
	UPROPERTY()
	UWebLink* WebLinkObject;
};
