// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Serialization/JsonSerializer.h"

class FDataJsonUtils
{
public:
	static TArray<TSharedPtr<FJsonValue>> ExtractDataArray(const FString& JsonString);
	static TSharedPtr<FJsonObject> ExtractDataObject(const FString& JsonString);
	static FString MakeDataPayload(const TSharedPtr<FJsonObject> DataObject);
};
