// Copyright © 2024 Ready Player Me


#include "ReadyPlayerMeMemoryCache.h"
#include "Utils/AvatarConfigProcessor.h"

namespace
{
	FString MakeAvatarConfigHash(UReadyPlayerMeAvatarConfig* AvatarConfig)
	{
		const FString UrlQueryString = FAvatarConfigProcessor::Process(AvatarConfig);
		return UrlQueryString.IsEmpty() ? "" : FMD5::HashAnsiString(*UrlQueryString).Left(8);
	}
}

FAvatarMemoryCacheData UReadyPlayerMeMemoryCache::GetAvatarCacheData(const FString& AvatarId, UReadyPlayerMeAvatarConfig* AvatarConfig) const
{
	const FString ConfigHash = MakeAvatarConfigHash(AvatarConfig);
	const auto CacheData = CachedAvatars.FindByPredicate([&AvatarId, &ConfigHash](const FAvatarMemoryCacheData& Data){return Data.AvatarId == AvatarId && Data.AvatarConfigHash == ConfigHash;});
	if (CacheData != nullptr)
	{
		return *CacheData;
	}
	return {};
}

void UReadyPlayerMeMemoryCache::AddAvatar(const FString& AvatarId, UReadyPlayerMeAvatarConfig* AvatarConfig, USkeletalMesh* SkeletalMesh, const FAvatarMetadata& Metadata)
{
	const FString ConfigHash = MakeAvatarConfigHash(AvatarConfig);
	const FAvatarMemoryCacheData CacheData = GetAvatarCacheData(AvatarId, AvatarConfig);
	if (CacheData.SkeletalMesh == nullptr)
	{
		CachedAvatars.Add({AvatarId, ConfigHash, SkeletalMesh, Metadata});
	}
}

void UReadyPlayerMeMemoryCache::ClearAvatar(const FString& AvatarId)
{
	CachedAvatars.RemoveAll([&AvatarId](const FAvatarMemoryCacheData& Data){return Data.AvatarId == AvatarId;});
}

void UReadyPlayerMeMemoryCache::ClearAvatars()
{
	CachedAvatars.Empty();
}
