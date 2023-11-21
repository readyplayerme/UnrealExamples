// Copyright © 2023++ Ready Player Me


#include "Endpoints.h"

static const TCHAR* API_ENDPOINT = TEXT("https://{0}.readyplayer.me/api{1}");
static const TCHAR* AVATAR_API_V2_ENDPOINT = TEXT("https://api.readyplayer.me/v2/avatars");
static const TCHAR* AVATAR_API_V1_ENDPOINT = TEXT("https://api.readyplayer.me/v1/avatars");
static const TCHAR* ASSET_ENDPOINT = TEXT("https://api.readyplayer.me/v1/assets?type={0}&limit={1}&page={2}&filter=viewable-by-user-and-app&filterUserId={3}&filterApplicationId={4}");
static const TCHAR* REQUEST_OPTIMIZATION_PARAMS = TEXT("morphTargets=none&textureAtlas=none&textureSizeLimit=768&lod=0&useHands=false");
static const TCHAR* MODELS_URL_PREFIX = TEXT("https://models.readyplayer.me");

FString FEndpoints::GetAuthAnonymousEndpoint(const FString& Subdomain)
{
	return FString::Format(API_ENDPOINT, {Subdomain, TEXT("/users")});
}

FString FEndpoints::GetAuthStartEndpoint(const FString& Subdomain)
{
	return FString::Format(API_ENDPOINT, {Subdomain, TEXT("/auth/start")});
}

FString FEndpoints::GetConfirmCodeEndpoint(const FString& Subdomain)
{
	return FString::Format(API_ENDPOINT, {Subdomain, TEXT("/auth/login")});
}

FString FEndpoints::GetTokenRefreshEndpoint(const FString& Subdomain)
{
	return FString::Format(API_ENDPOINT, {Subdomain, TEXT("/auth/refresh")});
}

FString FEndpoints::GetAssetEndpoint(const FString& AssetTypeStr, int32 Limit, int32 Page, const FString& UserId, const FString& AppId)
{
	return FString::Format(ASSET_ENDPOINT, { AssetTypeStr, Limit, Page, UserId, AppId});
}

FString FEndpoints::GetColorEndpoint(const FString& AvatarId)
{
	return FString::Format(TEXT("{0}/{1}/colors?type={2}"), {AVATAR_API_V2_ENDPOINT, AvatarId, TEXT("skin,beard,hair,eyebrow")});
}

FString FEndpoints::GetAvatarPublicUrl(const FString& AvatarId)
{
	return FString::Format(TEXT("{0}/{1}.glb"), {MODELS_URL_PREFIX, AvatarId});
}

FString FEndpoints::GetRenderEndpoint(const FString& AvatarId)
{
	return FString::Format(TEXT("{0}/{1}.png"), {MODELS_URL_PREFIX, AvatarId});
}

FString FEndpoints::GetUserAvatarsEndpoint(const FString& UserId)
{
	return FString::Format(TEXT("{0}?select=id,partner&userId={1}"), {AVATAR_API_V1_ENDPOINT, UserId});
}

FString FEndpoints::GetAvatarMetadataEndpoint(const FString& AvatarId)
{
	return FString::Format(TEXT("{0}/{1}.json"), {AVATAR_API_V2_ENDPOINT, AvatarId});
}

FString FEndpoints::GetCreateEndpoint()
{
	return AVATAR_API_V2_ENDPOINT;
}

FString FEndpoints::GetAvatarTemplatesEndpoint(const FString& TemplateId)
{
	return FString::Format(TEXT("{0}/{1}/{2}"), {AVATAR_API_V2_ENDPOINT, TEXT("templates"), TemplateId});
}

FString FEndpoints::GetAvatarModelEndpoint(const FString& AvatarId, bool bIsPreview)
{
	const FString PreviewParamStr = bIsPreview ? "preview=true&" : "";
	return FString::Format(TEXT("{0}/{1}.glb?{2}{3}"), {AVATAR_API_V2_ENDPOINT, AvatarId, PreviewParamStr, REQUEST_OPTIMIZATION_PARAMS});
}

FString FEndpoints::GetUpdateAvatarEndpoint(const FString& AvatarId)
{
	return FString::Format(TEXT("{0}/{1}?responseType=glb&{2}"), {AVATAR_API_V2_ENDPOINT, AvatarId, REQUEST_OPTIMIZATION_PARAMS});
}

FString FEndpoints::GetSaveAvatarEndpoint(const FString& AvatarId)
{
	return FString::Format(TEXT("{0}/{1}"), {AVATAR_API_V2_ENDPOINT, AvatarId});
}

FString FEndpoints::GetDeleteAvatarEndpoint(const FString& AvatarId, bool bIsDraft)
{
	const FString DraftStr = bIsDraft ? "draft" : "";
	return FString::Format(TEXT("{0}/{1}/{2}"), {AVATAR_API_V2_ENDPOINT, AvatarId, DraftStr});
}

FString FEndpoints::GetPrecompileEndpoint(const FString& AvatarId)
{
	return FString::Format(TEXT("{0}/{1}/precompile?{2}"), {AVATAR_API_V2_ENDPOINT, AvatarId, REQUEST_OPTIMIZATION_PARAMS});
}
