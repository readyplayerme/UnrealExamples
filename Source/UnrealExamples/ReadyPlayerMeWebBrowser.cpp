// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeWebBrowser.h"
#include "SWebBrowser.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "WebMessage.h"
#include "WebViewEvents.h"

static const FString LinkObjectName = TEXT("rpmlinkobject");
static const FString JavascriptPath = TEXT("ReadyPlayerMe/WebBrowser/Scripts/rpmFrameSetup.js");

static const TCHAR* ClearCacheParam = TEXT("clearCache");
static const TCHAR* QuickStartParam = TEXT("quickStart");
static const TCHAR* FullBodyParam = TEXT("bodyType=fullbody");
static const TCHAR* HalfBodyParam = TEXT("bodyType=halfbody");
static const TCHAR* SelectBodyTypeParam = TEXT("selectBodyType");
static const TCHAR* GenderMaleParam = TEXT("gender=male");
static const TCHAR* GenderFemaleParam = TEXT("gender=female");

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

void UReadyPlayerMeWebBrowser::SetupBrowser()
{
	BindBrowserToObject();
	const FString Path = FPaths::ProjectContentDir() / JavascriptPath;


	FString rpmSetupJavascript;
	if (FPaths::FileExists(Path))
	{
		FFileHelper::LoadFileToString(rpmSetupJavascript, *Path);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Script file not found: %s"), *Path);
		return;
	}

	ExecuteJavascript(rpmSetupJavascript);
}

void UReadyPlayerMeWebBrowser::BindBrowserToObject()
{
	if (!WebLinkObject)
	{
		WebLinkObject = NewObject<UWebLink>(this, *LinkObjectName);
	}
	WebLinkObject->SetWebBrowser(*this);
	WebBrowserWidget->BindUObject(LinkObjectName, WebLinkObject);
}

void UReadyPlayerMeWebBrowser::HandleEvents(WebMessage WebMessage)
{
	if (WebMessage.EventName == WebViewEvents::USER_SET)
	{
		if (OnUserSet.IsBound())
		{
			OnUserSet.Broadcast(WebMessage.GetId());
		}
	}
	else if (WebMessage.EventName == WebViewEvents::USER_AUTHORIZED)
	{
		if (OnUserAuthorized.IsBound())
		{
			OnUserAuthorized.Broadcast(WebMessage.GetUserId());
		}
	}
	else if (WebMessage.EventName == WebViewEvents::AVATAR_EXPORT)
	{
		if (OnAvatarExported.IsBound())
		{
			OnAvatarExported.Broadcast(WebMessage.GetUrl());
		}
	}
	else if (WebMessage.EventName == WebViewEvents::ASSET_UNLOCK)
	{
		if (OnAssetUnlock.IsBound())
		{
			OnAssetUnlock.Broadcast(WebMessage.GetAssetRecord());
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("WebEvent: %s"), *WebMessage.EventName);
}

void UReadyPlayerMeWebBrowser::AddBodyTypeParam(TArray<FString>& Params) const
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

void UReadyPlayerMeWebBrowser::AddGenderParam(TArray<FString>& Params) const
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

TSharedRef<SWidget> UReadyPlayerMeWebBrowser::RebuildWidget()
{
	TArray<FString> Params;
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

	InitialURL = FString::Printf(
		TEXT("https://%s.readyplayer.me%s/avatar%s&frameApi"), *PartnerDomain, *LanguageStr, *UrlQueryStr);

	return Super::RebuildWidget();
}
