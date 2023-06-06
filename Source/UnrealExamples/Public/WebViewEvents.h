// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WebViewEvents.generated.h"

USTRUCT()
struct FWebMessage
{
	GENERATED_BODY()

	UPROPERTY()
	FString type;

	UPROPERTY()
	FString source;

	UPROPERTY()
	FString eventName;

	UPROPERTY()
	TMap<FString, FString> data;
};

/**
 * 
 */
class UNREALEXAMPLES_API WebViewEvents
{
public:
	WebViewEvents();
	~WebViewEvents();

	// Conversion function
	static FWebMessage ConvertJsonStringToWebMessage(const FString& JsonString);

	// Declare your string constants.
	static const FString AVATAR_EXPORT;
	static const FString USER_SET;
	static const FString USER_AUTHORIZED;
	static const FString ASSET_UNLOCK;
};
