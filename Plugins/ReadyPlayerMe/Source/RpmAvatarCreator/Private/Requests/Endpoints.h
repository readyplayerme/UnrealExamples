// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"

class FEndpoints
{
public:
	static FString GetAuthAnonymousEndpoint(const FString& Subdomain);
	
	static FString GetAuthStartEndpoint(const FString& Subdomain);
	
	static FString GetConfirmCodeEndpoint(const FString& Subdomain);

	static FString GetTokenRefreshEndpoint(const FString& Subdomain);

	static FString GetAvatarTemplatesEndpoint(const FString& TemplateId = "");

	static FString GetAssetEndpoint(const FString& AssetTypeStr, int32 Limit, int32 Page, const FString& UserId, const FString& AppId);

	static FString GetColorEndpoint(const FString& AvatarId);

	static FString GetAvatarPublicUrl(const FString& AvatarId);

	static FString GetRenderEndpoint(const FString& AvatarId);

	static FString GetUserAvatarsEndpoint(const FString& UserId);

	static FString GetAvatarMetadataEndpoint(const FString& AvatarId);

	static FString GetCreateEndpoint();

	static FString GetAvatarModelEndpoint(const FString& AvatarId, bool bIsPreview);

	static FString GetUpdateAvatarEndpoint(const FString& AvatarId);

	static FString GetSaveAvatarEndpoint(const FString& AvatarId);

	static FString GetDeleteAvatarEndpoint(const FString& AvatarId, bool bIsDraft);

	static FString GetPrecompileEndpoint(const FString& AvatarId);
};