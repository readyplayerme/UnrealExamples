// Copyright © 2021++ Ready Player Me

#pragma once

#include "WebMessage.h"

class FWebViewEvents
{
public:
	static FWebMessage ConvertJsonStringToWebMessage(const FString& JsonString);

	static const FString AVATAR_EXPORT;
	static const FString USER_SET;
	static const FString USER_AUTHORIZED;
	static const FString ASSET_UNLOCK;
	
private:
	static const FString DATA_FIELD;
	static const FString TYPE_FIELD;
	static const FString SOURCE_FIELD;
	static const FString EVENT_NAME_FIELD;
};
