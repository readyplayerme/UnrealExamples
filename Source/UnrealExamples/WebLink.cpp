// Copyright © 2021++ Ready Player Me


#include "WebLink.h"
#include "ReadyPlayerMeWebBrowser.h"
#include "WebMessage.h"
#include "WebViewEvents.h"

void UWebLink::EventReceived(const FString JsonResponse)
{
	const WebMessage WebMessage = WebViewEvents::ConvertJsonStringToWebMessage(JsonResponse);
	WebBrowser->HandleEvents(WebMessage);
}
