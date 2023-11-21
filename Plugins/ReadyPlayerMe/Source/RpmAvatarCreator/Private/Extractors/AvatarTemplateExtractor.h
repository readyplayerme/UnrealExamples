// Copyright © 2023++ Ready Player Me

#pragma once

#include "RpmAvatarCreatorTypes.h"

class FAvatarTemplateExtractor
{
public:
	static TArray<FRpmAvatarTemplate> ExtractAvatarTemplates(const FString& JsonString);
};
