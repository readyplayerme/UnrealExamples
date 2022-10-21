// Copyright © 2021++ Ready Player Me


#include "Utils/ReadyPlayerMeUrlConvertor.h"

#include "ReadyPlayerMeAvatarConfigProcessor.h"
#include "Internationalization/Regex.h"

static const FString SHORTCODE_URL_PREFIX = "https://api.readyplayer.me/v1/avatars/";
static const FString URL_PATTERN = "https?:\\/\\/(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,4}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)";
static const FString SHORTCODE_PATTERN = "^[a-zA-Z0-9]*$";
static const TCHAR* SUFFIX_GLB = TEXT(".glb");
static const TCHAR* SUFFIX_JSON = TEXT(".json");
static const TCHAR* AVATARS_FOLDER = TEXT("Avatars");
static const TCHAR* DEFAULT_FOLDER = TEXT("Default");

FString FReadyPlayerMeUrlConvertor::GetValidatedUrlShortCode(const FString& UrlShortCode)
{
	if (UrlShortCode.IsEmpty() || IsUrl(UrlShortCode))
	{
		return UrlShortCode;
	}
	if (IsShortcode(UrlShortCode))
	{
		return SHORTCODE_URL_PREFIX + UrlShortCode + SUFFIX_GLB;
	}
	return "";
}

bool FReadyPlayerMeUrlConvertor::IsShortcode(const FString& Shortcode)
{
	const FRegexPattern RegexPattern(SHORTCODE_PATTERN);
	FRegexMatcher RegexMatcher(RegexPattern, Shortcode);
	return RegexMatcher.FindNext();
}

bool FReadyPlayerMeUrlConvertor::IsUrl(const FString& Url)
{
	const FRegexPattern RegexPattern(URL_PATTERN);
	FRegexMatcher RegexMatcher(RegexPattern, Url);
	return RegexMatcher.FindNext();
}

FAvatarUri FReadyPlayerMeUrlConvertor::CreateAvatarUri(const FString& Url, UReadyPlayerMeAvatarConfig* AvatarConfig)
{
	FString UrlLink, UrlQueryString;
	if (!Url.Split(TEXT("?"), &UrlLink, &UrlQueryString))
	{
		UrlLink = Url;
	}
	UrlQueryString = FReadyPlayerMeAvatarConfigProcessor::Process(AvatarConfig);
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

	return AvatarUri;
}
