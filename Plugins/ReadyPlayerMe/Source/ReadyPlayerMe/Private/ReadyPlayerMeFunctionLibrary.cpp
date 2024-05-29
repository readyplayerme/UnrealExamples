// Copyright © 2024 Ready Player Me


#include "ReadyPlayerMeFunctionLibrary.h"

#include "ReadyPlayerMeGameSubsystem.h"
#include "ReadyPlayerMeMemoryCache.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Storage/AvatarManifest.h"
#include "Storage/AvatarStorage.h"
#include "Utils/AvatarUrlConvertor.h"

void UReadyPlayerMeFunctionLibrary::ClearAvatarCache(const UObject* WorldContextObject)
{
	FAvatarStorage::ClearCache();
    const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
    const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GameInstance);
    GameSubsystem->AvatarManifest->Clear();
}

void UReadyPlayerMeFunctionLibrary::ClearAvatarFromCache(const UObject* WorldContextObject, const FString& AvatarId)
{
    FAvatarStorage::ClearAvatar(AvatarId);
    const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
    const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GameInstance);
    GameSubsystem->AvatarManifest->ClearAvatar(AvatarId);
}

bool UReadyPlayerMeFunctionLibrary::IsAvatarCacheEmpty()
{
    return FAvatarStorage::IsCacheEmpty();
}

int32 UReadyPlayerMeFunctionLibrary::GetCachedAvatarCount()
{
    return FAvatarStorage::GetSavedAvatars().Num();
}

int64 UReadyPlayerMeFunctionLibrary::GetAvatarCacheSize()
{
    return FAvatarStorage::GetCacheSize();
}

FString UReadyPlayerMeFunctionLibrary::GetAvatarId(const FString& Url)
{
    return FAvatarUrlConvertor::GetAvatarId(Url);
}

void UReadyPlayerMeFunctionLibrary::ClearAvatarsFromMemory(const UObject* WorldContextObject)
{
    const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
    const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GameInstance);
    GameSubsystem->MemoryCache->ClearAvatars();
}

void UReadyPlayerMeFunctionLibrary::ClearAvatarFromMemory(const UObject* WorldContextObject, const FString& AvatarId)
{
    const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
    const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GameInstance);
    GameSubsystem->MemoryCache->ClearAvatar(FAvatarUrlConvertor::GetAvatarId(AvatarId));
}
