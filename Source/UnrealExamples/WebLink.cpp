// Fill out your copyright notice in the Description page of Project Settings.


#include "WebLink.h"

#include "ReadyPlayerMeWebBrowser.h"
#include "Public/WebViewEvents.h"

void UWebLink::EventReceived(FString JsonResponse)
{
	UE_LOG(LogTemp, Warning, TEXT("EVENT RECEIVED!!! %p"), &JsonResponse);
	const FWebMessage WebMessage = WebViewEvents::ConvertJsonStringToWebMessage(JsonResponse);
	WebBrowser->HandleEvents(WebMessage);
}
