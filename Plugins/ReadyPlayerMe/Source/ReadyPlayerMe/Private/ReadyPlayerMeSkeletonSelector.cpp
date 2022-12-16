// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeSkeletonSelector.h"

const FSkeletonProperties* UReadyPlayerMeSkeletonSelector::GetSelectedSkeletonProperties(const FAvatarMetadata& Metadata) const
{
	if (Metadata.BodyType == EAvatarBodyType::HalfBody)
	{
		if (Skeletons.Contains(ESkeletonType::HalfBody))
		{
			return &Skeletons[ESkeletonType::HalfBody];
		}
	}
	else
	{
		if (Metadata.OutfitGender == EAvatarGender::Masculine && Skeletons.Contains(ESkeletonType::Male))
		{
			return &Skeletons[ESkeletonType::Male];
		}
		if (Metadata.OutfitGender == EAvatarGender::Feminine && Skeletons.Contains(ESkeletonType::Female))
		{
			return &Skeletons[ESkeletonType::Female];
		}
	}
	return nullptr;
}
