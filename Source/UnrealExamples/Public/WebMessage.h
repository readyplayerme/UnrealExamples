// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UNREALEXAMPLES_API WebMessage
{
public:
	FString Type;
	FString Source;
	FString EventName;
	TMap<FString, FString> Data;


	FString GetDataValue(const FString& Key);
	FString GetId();
	FString GetUserId();
	FString GetUrl();
	struct FAssetRecord GetAssetRecord();
};
