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
	HalfBody
};

UENUM(BlueprintType)
enum class ESelectGender : uint8
{
	None,
	Male,
	Female
};

UENUM(BlueprintType)
enum class ELanguage : uint8
{
	Default UMETA(DisplayName = "Default"),
	En UMETA(DisplayName = "English"),
	EnIe UMETA(DisplayName = "English (Ireland)"),
	De UMETA(DisplayName = "German"),
	Fr UMETA(DisplayName = "French"),
	Es UMETA(DisplayName = "Spanish"),
	EsMx UMETA(DisplayName = "Spanish (Mexican)"),
	Pt UMETA(DisplayName = "Portuguese"),
	PtBr UMETA(DisplayName = "Portuguese (Brazil)"),
	It UMETA(DisplayName = "Italian"),
	Tr UMETA(DisplayName = "Turkish"),
	Jp UMETA(DisplayName = "Japanese"),
	Kr UMETA(DisplayName = "Korean"),
	Ch UMETA(DisplayName = "Chinese"),
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
	void SetupBrowser();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Bind Browser To Object"), Category = "Ready Player Me|Web Browser")
	void BindBrowserToObject();
	
	void HandleEvents(const struct FWebMessage& JsonResponse);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	FString PartnerDomain = "demo";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	bool bClearCache = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	bool bQuickStart = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	ESelectBodyType SelectBodyType = ESelectBodyType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	ESelectGender SelectGender = ESelectGender::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	ELanguage Language = ELanguage::Default;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	
	UPROPERTY()
	UWebLink* WebLinkObject;

private:
	void AddBodyTypeParam(TArray<FString>& Params) const;
	void AddGenderParam(TArray<FString>& Params) const;
};
