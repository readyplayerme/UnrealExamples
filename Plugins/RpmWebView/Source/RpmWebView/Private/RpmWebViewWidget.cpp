// Copyright © 2021++ Ready Player Me

#include "RpmWebViewWidget.h"
#include "SWebBrowser.h"
#include "WebMessage.h"
#include "WebBrowserEvents.h"
#include "FrameSetupJs.h"
#include "ReadyPlayerMeSettings.h"

static const TCHAR* LinkObjectName = TEXT("rpmlinkobject");
static const TCHAR* ClearCacheParam = TEXT("clearCache");
static const TCHAR* QuickStartParam = TEXT("quickStart");
static const TCHAR* FullBodyParam = TEXT("bodyType=fullbody");
static const TCHAR* HalfBodyParam = TEXT("bodyType=halfbody");
static const TCHAR* SelectBodyTypeParam = TEXT("selectBodyType");
static const TCHAR* GenderMaleParam = TEXT("gender=male");
static const TCHAR* GenderFemaleParam = TEXT("gender=female");
static const TCHAR* LoginTokenParam = TEXT("token");
static const TCHAR* FrameApiParam = TEXT("frameApi");

static const TMap<ELanguage, FString> LANGUAGE_TO_STRING =
{
	{ELanguage::En, "en"},
	{ELanguage::EnIe, "en-IE"},
	{ELanguage::De, "de"},
	{ELanguage::Fr, "fr"},
	{ELanguage::Es, "es"},
	{ELanguage::EsMx, "es-MX"},
	{ELanguage::Pt, "pt"},
	{ELanguage::PtBr, "pt-BR"},
	{ELanguage::It, "it"},
	{ELanguage::Tr, "tr"},
	{ELanguage::Jp, "jp"},
	{ELanguage::Kr, "kr"},
	{ELanguage::Ch, "ch"}
};

void URpmWebViewWidget::SetupBrowser()
{
	Rename(LinkObjectName);
	WebBrowserWidget->BindUObject(LinkObjectName, this);
	ExecuteJavascript(RPM_SETUP_JAVASCRIPT);
}

void URpmWebViewWidget::HandleEvents(const FString& JsonResponse) const
{
	const FWebMessage WebMessage = FWebViewEvents::ConvertJsonStringToWebMessage(JsonResponse);
	if (WebMessage.EventName == FWebViewEvents::USER_SET)
	{
		if (OnUserSet.IsBound())
		{
			OnUserSet.Broadcast(WebMessage.GetId());
		}
	}
	else if (WebMessage.EventName == FWebViewEvents::USER_AUTHORIZED)
	{
		if (OnUserAuthorized.IsBound())
		{
			OnUserAuthorized.Broadcast(WebMessage.GetUserId());
		}
	}
	else if (WebMessage.EventName == FWebViewEvents::AVATAR_EXPORT)
	{
		if (OnAvatarExported.IsBound())
		{
			OnAvatarExported.Broadcast(WebMessage.GetUrl());
		}
	}
	else if (WebMessage.EventName == FWebViewEvents::ASSET_UNLOCK)
	{
		if (OnAssetUnlock.IsBound())
		{
			OnAssetUnlock.Broadcast(WebMessage.GetAssetRecord());
		}
	}
	UE_LOG(LogTemp, Log, TEXT("WebEvent: %s"), *WebMessage.EventName);
}

void URpmWebViewWidget::AddBodyTypeParam(TArray<FString>& Params) const
{
	switch (SelectBodyType)
	{
	case ESelectBodyType::FullBody:
		Params.Add(FullBodyParam);
		break;
	case ESelectBodyType::HalfBody:
		Params.Add(HalfBodyParam);
		break;
	case ESelectBodyType::Select:
		Params.Add(SelectBodyTypeParam);
		break;
	default:
		break;
	}
}

void URpmWebViewWidget::AddGenderParam(TArray<FString>& Params) const
{
	switch (SelectGender)
	{
	case ESelectGender::Male:
		Params.Add(GenderMaleParam);
		break;
	case ESelectGender::Female:
		Params.Add(GenderFemaleParam);
		break;
	default:
		break;
	}
}

FString URpmWebViewWidget::BuildUrl(const FString& LoginToken) const
{
	TArray<FString> Params;
	if(!LoginToken.IsEmpty())
	{
		Params.Add(LoginTokenParam + '=' + LoginToken);
	}
	
	Params.Add(FrameApiParam);
	if (bClearCache)
	{
		Params.Add(ClearCacheParam);
	}
	if (bQuickStart)
	{
		Params.Add(QuickStartParam);
	}
	AddBodyTypeParam(Params);
	AddGenderParam(Params);

	FString UrlQueryStr;
	if (!Params.IsEmpty())
	{
		UrlQueryStr = "?" + FString::Join(Params, TEXT("&"));
	}
	FString LanguageStr;
	if (Language != ELanguage::Default)
	{
		LanguageStr = "/" + LANGUAGE_TO_STRING[Language];
	}

	const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
	return FString::Printf(
		TEXT("https://%s.readyplayer.me%s/avatar%s"), *Settings->Subdomain, *LanguageStr, *UrlQueryStr);
}

void URpmWebViewWidget::EventReceived(const FString JsonResponse)
{
	HandleEvents(JsonResponse);
}


void URpmWebViewWidget::HandleUrlChanged(const FText& Text)
{
	const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
	const bool bIsSubdomainSet = IsValid(Settings) && !Settings->Subdomain.IsEmpty();
	checkf(bIsSubdomainSet, TEXT("Application subdomain is required for the webview. Find the subdomain of your application from the Ready Player Me studio website, and set it in your project settings under the ReadyPlayerMe > Subdomain"));
	SetupBrowser();
	OnUrlChanged.RemoveAll(this);
}

TSharedRef<SWidget> URpmWebViewWidget::RebuildWidget()
{
	InitialURL = BuildUrl();
	if (!IsDesignTime())
	{
		OnUrlChanged.AddUniqueDynamic(this, &URpmWebViewWidget::HandleUrlChanged);
	}

	return Super::RebuildWidget();
}
