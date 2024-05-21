// Copyright © 2024 Ready Player Me


#include "AvatarUrlConvertor.h"

#include "ReadyPlayerMeAvatarConfig.h"
#include "AvatarConfigProcessor.h"
#include "ReadyPlayerMeAutoLodConfig.h"
#include "Internationalization/Regex.h"
#include "Misc/Paths.h"

static const FString ID_URL_PREFIX = "https://models.readyplayer.me/";
static const FString URL_PATTERN = "https?:\\/\\/(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,4}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)";
static const FString ID_PATTERN = "^[a-zA-Z0-9]*$";
static const TCHAR* SUFFIX_GLB = TEXT(".glb");
static const TCHAR* SUFFIX_JSON = TEXT(".json");
static const TCHAR* AVATARS_FOLDER = TEXT("Avatars");
static const TCHAR* DEFAULT_FOLDER = TEXT("Default");

FString FAvatarUrlConvertor::GetValidatedUrl(const FString& IdUrl)
{
	if (IdUrl.IsEmpty() || IsUrl(IdUrl))
	{
		return IdUrl;
	}
	if (IsId(IdUrl))
	{
		return ID_URL_PREFIX + IdUrl + SUFFIX_GLB;
	}
	return "";
}

bool FAvatarUrlConvertor::IsId(const FString& Id)
{
	const FRegexPattern RegexPattern(ID_PATTERN);
	FRegexMatcher RegexMatcher(RegexPattern, Id);
	return RegexMatcher.FindNext();
}

bool FAvatarUrlConvertor::IsUrl(const FString& Url)
{
	const FRegexPattern RegexPattern(URL_PATTERN);
	FRegexMatcher RegexMatcher(RegexPattern, Url);
	return RegexMatcher.FindNext();
}

FString FAvatarUrlConvertor::GetAvatarId(const FString& IdUrl)
{
	if (IdUrl.IsEmpty())
	{
		return "";
	}
	if (IsId(IdUrl))
	{
		return IdUrl;
	}
	const FAvatarUri Uri = CreateAvatarUri(IdUrl);
	return Uri.Guid;
}

FAvatarUri FAvatarUrlConvertor::CreateAvatarUri(const FString& Url, UReadyPlayerMeAvatarConfig* AvatarConfig, UReadyPlayerMeAutoLodConfig* AutoLodConfig)
{
	FString UrlLink, UrlQueryString;
	if (!Url.Split(TEXT("?"), &UrlLink, &UrlQueryString))
	{
		UrlLink = Url;
	}
	UrlQueryString = FAvatarConfigProcessor::Process(AvatarConfig);
	FString Path, Guid, Extension;
	FPaths::Split(UrlLink, Path, Guid, Extension);
	const FString UrlPath = Path + "/" + Guid;

	FAvatarUri AvatarUri;
	AvatarUri.Guid = Guid;
	AvatarUri.ModelUrl = UrlPath + SUFFIX_GLB + UrlQueryString;
	AvatarUri.MetadataUrl = UrlPath + SUFFIX_JSON;

	const FString AvatarsFolder = FPaths::ProjectPersistentDownloadDir() + "/" + AVATARS_FOLDER + "/" + Guid;
	const FString ModelFolderName = UrlQueryString.IsEmpty() ? DEFAULT_FOLDER : FMD5::HashAnsiString(*UrlQueryString).Left(8);
	AvatarUri.LocalAvatarDirectory = AvatarsFolder;
	AvatarUri.LocalModelPath = AvatarsFolder + "/" + ModelFolderName + "/" + Guid + SUFFIX_GLB;
	AvatarUri.LocalMetadataPath = AvatarsFolder + "/" + Guid + SUFFIX_JSON;
	if (AutoLodConfig)
	{
		for (auto* Config : AutoLodConfig->AutoLodConfigs)
		{
			const FString LodUrlQueryString = FAvatarConfigProcessor::Process(Config);
			AvatarUri.ModelLodUrls.Add(UrlPath + SUFFIX_GLB + LodUrlQueryString);
			AvatarUri.LocalModelLodPaths.Add(AvatarsFolder + "/" + FMD5::HashAnsiString(*LodUrlQueryString).Left(8) + "/" + Guid + SUFFIX_GLB);
		}
	}
	return AvatarUri;
}
