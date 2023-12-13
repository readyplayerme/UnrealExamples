// Copyright © 2021++ Ready Player Me

#pragma once

#include "WebBrowser.h"
#include "RpmWebViewTypes.h"
#include "RpmWebViewWidget.generated.h"

UCLASS(BlueprintType)
class RPMWEBVIEW_API URpmWebViewWidget : public UWebBrowser
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me|Web Browser")
	bool bClearCache = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me|Web Browser")
	ESelectBodyType SelectBodyType = ESelectBodyType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me|Web Browser")
	ESelectGender SelectGender = ESelectGender::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me|Web Browser")
	ELanguage Language = ELanguage::Default;
	
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me|Web Browser")
	void EventReceived(const FString JsonResponse);

	UPROPERTY(BlueprintAssignable)
	FOnAvatarCreated OnAvatarExported;

	UPROPERTY(BlueprintAssignable)
	FOnUserSet OnUserSet;

	UPROPERTY(BlueprintAssignable)
	FOnAssetUnlock OnAssetUnlock;

	UPROPERTY(BlueprintAssignable)
	FOnUserAuthorized OnUserAuthorized;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	UFUNCTION()
	void HandleUrlChanged(const FText& Text);
	
	void SetupBrowser();
	void HandleEvents(const FString& JsonResponse) const;
	void AddBodyTypeParam(TArray<FString>& Params) const;
	void AddGenderParam(TArray<FString>& Params) const;
	FString BuildUrl(const FString& LoginToken = FString()) const;
};
