// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeWebBrowser.h"

static const FString LinkObjectName = TEXT("rpmlinkobject");
static const FString JSAddAvatarGeneratedListener = TEXT("window.addEventListener('message', function(event){ window.ue.rpmlinkobject.avatargenerated(event.data);});");

static const TCHAR* ClearCacheParam = TEXT("clearCache");
static const TCHAR* QuickStartParam = TEXT("quickStart");
static const TCHAR* FullBodyParam = TEXT("bodyType=fullbody");
static const TCHAR* HalfBodyParam = TEXT("bodyType=halfbody");
static const TCHAR* SelectBodyTypeParam = TEXT("selectBodyType");
static const TCHAR* GenderMaleParam = TEXT("gender=male");
static const TCHAR* GenderFemaleParam = TEXT("gender=female");

static const TMap<ELanguage, FString> LANGUAGE_TO_STRING =
{
	{ ELanguage::En, "en" },
	{ ELanguage::EnIe, "en-IE" },
	{ ELanguage::De, "de" },
	{ ELanguage::Fr, "fr" },
	{ ELanguage::Es, "es" },
	{ ELanguage::EsMx, "es-MX" },
	{ ELanguage::Pt, "pt" },
	{ ELanguage::PtBr, "pt-BR" },
	{ ELanguage::It, "it" },
	{ ELanguage::Tr, "tr" },
	{ ELanguage::Jp, "jp" },
	{ ELanguage::Kr, "kr" },
	{ ELanguage::Ch, "ch" }
};

void UReadyPlayerMeWebBrowser::SetupBrowser(const FReadyPlayerWebBrowserResponse& Response)
{
	BindBrowserToObject();
	WebLinkObject->SetAvatarUrlCallback(Response);
	ExecuteJavascript(JSAddAvatarGeneratedListener);
}

void UReadyPlayerMeWebBrowser::BindBrowserToObject()
{
	if (!WebLinkObject) {
		WebLinkObject = NewObject<UWebLink>(this, *LinkObjectName);
	}
	WebBrowserWidget->BindUObject(LinkObjectName, WebLinkObject);
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

	InitialURL = FString::Printf(TEXT("https://%s.readyplayer.me%s/avatar%s"), *PartnerDomain, *LanguageStr, *UrlQueryStr);

	return Super::RebuildWidget();
}