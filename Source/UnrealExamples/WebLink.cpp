// Fill out your copyright notice in the Description page of Project Settings.


#include "WebLink.h"

#include "ReadyPlayerMeWebBrowser.h"
#include "Public/WebViewEvents.h"

void UWebLink::EventReceived(FString JsonResponse)
{
	const FWebMessage WebMessage = WebViewEvents::ConvertJsonStringToWebMessage(JsonResponse);
	WebBrowser->HandleEvents(WebMessage);
}
