// Copyright © 2024 Ready Player Me

#include "ReadyPlayerMeGameSubsystem.h"
#include "ReadyPlayerMeMemoryCache.h"

#include "Storage/AvatarManifest.h"

UReadyPlayerMeGameSubsystem::UReadyPlayerMeGameSubsystem()
	: MemoryCache(nullptr)
	, AvatarManifest(nullptr)
{}

void UReadyPlayerMeGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	MemoryCache = NewObject<UReadyPlayerMeMemoryCache>(this, TEXT("MemoryCache"));
	AvatarManifest = MakeShared<FAvatarManifest>();
}

void UReadyPlayerMeGameSubsystem::Deinitialize()
{
    MemoryCache->ClearAvatars();
	MemoryCache = nullptr;
	AvatarManifest.Reset();
}
