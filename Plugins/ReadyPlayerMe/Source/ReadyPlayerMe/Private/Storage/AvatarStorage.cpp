// Copyright © 2024 Ready Player Me


#include "AvatarStorage.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/FileManagerGeneric.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION > 4
#include "HAL/PlatformFileManager.h"
#else
#include "HAL/PlatformFilemanager.h"
#endif

namespace
{
	FString GetAvatarCacheDir()
	{
		return FPaths::Combine(FPaths::ProjectPersistentDownloadDir(), TEXT("Avatars"));
	}
}


FString FAvatarStorage::GetManifestFilePath()
{
	return FPaths::Combine(GetAvatarCacheDir(), TEXT("AvatarManifest.json"));
}

FString FAvatarStorage::LoadJson(const FString& Path)
{
	if (!Path.IsEmpty() && FPaths::FileExists(*Path))
	{
		FString ResultStr;
		if (FFileHelper::LoadFileToString(ResultStr, *Path))
		{
			return ResultStr;
		}
		UE_LOG(LogReadyPlayerMe, Warning, TEXT("Failed to load the json file"));
	}
	return "";
}

bool FAvatarStorage::AvatarExists(const FAvatarUri& AvatarUri)
{
	TArray<FString> Paths = {AvatarUri.LocalMetadataPath, AvatarUri.LocalModelPath};
	Paths.Append(AvatarUri.LocalModelLodPaths);
	bool AvatarExists = true;
	for (auto& Path : Paths)
	{
		AvatarExists = AvatarExists && FileExists(Path);
	}
	return AvatarExists;
}

bool FAvatarStorage::FileExists(const FString& Path)
{
	return !Path.IsEmpty() && FPaths::FileExists(*Path);
}

void FAvatarStorage::DeleteDirectory(const FString& Path)
{
	if (Path.IsEmpty())
	{
		return;
	}
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.DirectoryExists(*Path) && !PlatformFile.DeleteDirectoryRecursively(*Path))
	{
		UE_LOG(LogReadyPlayerMe, Warning, TEXT("Failed to delete directory"));
	}
}

void FAvatarStorage::SaveAvatar(const FString& GlbFilePath, const TArray<uint8>& Data)
{
	if (!FFileHelper::SaveArrayToFile(Data, *GlbFilePath))
	{
		UE_LOG(LogReadyPlayerMe, Warning, TEXT("Failed to save the downloaded file"));
	}
}

void FAvatarStorage::SaveJson(const FString& Path, const FString& Content)
{
	if (!FFileHelper::SaveStringToFile(Content, *Path))
	{
		UE_LOG(LogReadyPlayerMe, Warning, TEXT("Failed to save the json file"));
	}
}

void FAvatarStorage::ClearCache()
{
	DeleteDirectory(GetAvatarCacheDir());
}

bool FAvatarStorage::IsCacheEmpty()
{
	return GetSavedAvatars().Num() == 0;
}

void FAvatarStorage::ClearAvatar(const FString& Guid)
{
	DeleteDirectory(FPaths::Combine(GetAvatarCacheDir(), Guid));
}

TArray<FString> FAvatarStorage::GetSavedAvatars()
{
	const FString Path = FPaths::Combine(GetAvatarCacheDir(), TEXT("*"));
	
	TArray<FString> FoundDirs;
	IFileManager::Get().FindFiles(FoundDirs, *Path, false, true);
	for (auto& Dir : FoundDirs)
	{
		Dir = FPaths::GetBaseFilename(Dir);
	}
	return FoundDirs;
}

int64 FAvatarStorage::GetCacheSize()
{
	int64 DirectorySize = 0;
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	PlatformFile.IterateDirectoryRecursively(*GetAvatarCacheDir(),
		[&DirectorySize, &PlatformFile](const TCHAR* Filename, bool bIsDirectory) -> bool
		{
			if (!bIsDirectory && !FCString::Strstr(Filename, TEXT("AvatarManifest.json")))
			{
				DirectorySize += PlatformFile.FileSize(Filename);
			}
			return true;
		});
	return DirectorySize;
}
