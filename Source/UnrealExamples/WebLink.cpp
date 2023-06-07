// Fill out your copyright notice in the Description page of Project Settings.


#include "WebLink.h"
#include "ReadyPlayerMeWebBrowser.h"
#include "WebMessage.h"
#include "WebViewEvents.h"

void UWebLink::EventReceived(const FString JsonResponse)
{
	const WebMessage WebMessage = WebViewEvents::ConvertJsonStringToWebMessage(JsonResponse);
	WebBrowser->HandleEvents(WebMessage);
}
