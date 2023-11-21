// Copyright © 2023++ Ready Player Me

#pragma once

#include "RpmAvatarCreatorTypes.h"

class FUserAvatarExtractor
{
public:
	static TArray<FRpmUserAvatar> ExtractUserAvatars(const FString& JsonString);
};
