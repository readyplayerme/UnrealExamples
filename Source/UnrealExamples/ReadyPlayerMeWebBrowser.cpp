// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeWebBrowser.h"

static const FString LinkObjectName = TEXT("rpmlinkobject");
static const FString JSAddAvatarGeneratedListener = TEXT("window.addEventListener('message', function(event){ window.ue.rpmlinkobject.avatargenerated(event.data);});");

static const TCHAR* ClearCacheParam = TEXT("clearCache");
static const TCHAR* FullBodyParam = TEXT("bodyType=fullbody");
static const TCHAR* HalfBodyParam = TEXT("bodyType=halfbody");
static const TCHAR* SelectBodyTypeParam = TEXT("selectBodyType");
static const TCHAR* GenderMaleParam = TEXT("gender=male");
static const TCHAR* GenderFemaleParam = TEXT("gender=female");


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

TSharedRef<SWidget> UReadyPlayerMeWebBrowser::RebuildWidget()
{
	TArray<FString> Params;
	if (bClearCache)
	{
		Params.Add(ClearCacheParam);
	}
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

	if (!Params.IsEmpty() && !InitialURL.IsEmpty())
	{
		FString UrlLink, UrlQueryString;
		if (InitialURL.Split(TEXT("?"), &UrlLink, &UrlQueryString))
		{
			InitialURL = UrlLink;
		}
		InitialURL += "?" + FString::Join(Params, TEXT("&"));
	}

	return Super::RebuildWidget();
}