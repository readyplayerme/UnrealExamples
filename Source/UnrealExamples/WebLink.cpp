// Fill out your copyright notice in the Description page of Project Settings.


#include "WebLink.h"

void UWebLink::AvatarGenerated(FString JsonResponse)
{
	FString Url = "";
	if (JsonResponse.Contains(TEXT(".glb")))
	{
		UE_LOG(LogTemp, Warning, TEXT(".glb found "));
		Url = JsonResponse;
	}
	if (Url.IsEmpty())
	{
		return;
	}

	WebBrowserResponse.Execute(Url);
	LastAvatarUrl = Url;
}

void UWebLink::SetAvatarUrlCallback(const FReadyPlayerWebBrowserResponse& WebBrowserCallback)
{
	WebBrowserResponse = WebBrowserCallback;
}

FString UWebLink::GetLastAvatarUrl()
{
	return LastAvatarUrl;
}

