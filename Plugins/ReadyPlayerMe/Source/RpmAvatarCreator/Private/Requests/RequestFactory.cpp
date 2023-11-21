// Copyright © 2023++ Ready Player Me


#include "RequestFactory.h"

#include "CoreMinimal.h"
#include "BaseRequest.h"
#include "Endpoints.h"
#include "Extractors/UserDataExtractor.h"

constexpr float IMAGE_REQUEST_TIMEOUT = 60.f;

FRequestFactory::FRequestFactory()
	: CancellationDelegate(MakeShared<FCancellationDelegate>())
{
}

void FRequestFactory::SetSubdomain(const FString& InSubdomain)
{
	Subdomain = InSubdomain;
}

FString FRequestFactory::GetSubdomain() const
{
	return Subdomain;
}

void FRequestFactory::SetAppId(const FString& InAppId)
{
	AppId = InAppId;
}

FString FRequestFactory::GetAppId() const
{
	return AppId;
}

void FRequestFactory::SetUserData(const FRpmUserData& Data)
{
	UserData = Data;
}

void FRequestFactory::SetTokenRefreshedDelegate(const FTokenRefreshed& TokenRefreshed)
{
	TokenRefreshedDelegate = TokenRefreshed;
}

void FRequestFactory::SetSessionExpiredDelegate(const FSessionExpired& SessionExpired)
{
	SessionExpiredDelegate = SessionExpired;
}

void FRequestFactory::CancelRequests() const
{
	CancellationDelegate->Broadcast();
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateAuthStartRequest(const FString& PayloadJson) const
{
	return CreateBaseRequest(FEndpoints::GetAuthStartEndpoint(Subdomain), ERequestVerb::Post, PayloadJson);
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateConfirmCodeRequest(const FString& PayloadJson) const
{
	return CreateBaseRequest(FEndpoints::GetConfirmCodeEndpoint(Subdomain), ERequestVerb::Post, PayloadJson);
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateTokenRefreshRequest() const
{
	return CreateBaseRequest(FEndpoints::GetTokenRefreshEndpoint(Subdomain), ERequestVerb::Post, FUserDataExtractor::MakeTokenRefreshPayload(UserData));
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateAuthAnonymousRequest() const
{
	return CreateBaseRequest(FEndpoints::GetAuthAnonymousEndpoint(Subdomain), ERequestVerb::Post);
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateAvatarTemplatesRequest() const
{
	return CreateAuthorizedRequest(FEndpoints::GetAvatarTemplatesEndpoint());
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateAssetRequest(const FString& AssetTypeStr, int32 Limit, int32 Page) const
{
	return CreateAuthorizedRequest(FEndpoints::GetAssetEndpoint(AssetTypeStr, Limit, Page, UserData.Id, AppId));
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateColorRequest(const FString& AvatarId) const
{
	return CreateAuthorizedRequest(FEndpoints::GetColorEndpoint(AvatarId));
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateImageRequest(const FString& IconUrl) const
{
	return CreateBaseRequest(IconUrl);
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateRenderRequest(const FString& AvatarId) const
{
	return CreateBaseRequest(FEndpoints::GetRenderEndpoint(AvatarId), ERequestVerb::Get, "", IMAGE_REQUEST_TIMEOUT);
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateUserAvatarsRequest() const
{
	return CreateAuthorizedRequest(FEndpoints::GetUserAvatarsEndpoint(UserData.Id));
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateAvatarModelRequest(const FString& AvatarId, bool bIsPreview) const
{
	return CreateBaseRequest(FEndpoints::GetAvatarModelEndpoint(AvatarId, bIsPreview));
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateAvatarMetadataRequest(const FString& AvatarId) const
{
	return CreateBaseRequest(FEndpoints::GetAvatarMetadataEndpoint(AvatarId));
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateAvatarCreateRequest(const FString& PayloadJson, const FString& TemplateId) const
{
	if (TemplateId.IsEmpty())
	{
		return CreateAuthorizedRequest(FEndpoints::GetCreateEndpoint(), ERequestVerb::Post, PayloadJson);
	}
	return CreateAuthorizedRequest(FEndpoints::GetAvatarTemplatesEndpoint(TemplateId), ERequestVerb::Post, PayloadJson);
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateUpdateAvatarRequest(const FString& AvatarId, const FString& PayloadJson) const
{
	return CreateAuthorizedRequest(FEndpoints::GetUpdateAvatarEndpoint(AvatarId), ERequestVerb::Patch, PayloadJson);
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateSaveAvatarRequest(const FString& AvatarId) const
{
	return CreateAuthorizedRequest(FEndpoints::GetSaveAvatarEndpoint(AvatarId), ERequestVerb::Put);
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateDeleteAvatarRequest(const FString& AvatarId, bool bIsDraft) const
{
	return CreateAuthorizedRequest(FEndpoints::GetDeleteAvatarEndpoint(AvatarId, bIsDraft), ERequestVerb::Delete);
}

TSharedPtr<IBaseRequest> FRequestFactory::CreatePrecompileRequest(const FString& AvatarId, const FString& PayloadJson) const
{
	return CreateAuthorizedRequest(FEndpoints::GetPrecompileEndpoint(AvatarId), ERequestVerb::Post, PayloadJson);
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateBaseRequest(const FString& Url, ERequestVerb RequestVerb, const FString& Payload, float Timeout) const
{
	return MakeShared<FBaseRequest>(CancellationDelegate, Url, "", RequestVerb, Payload, Timeout);
}

TSharedPtr<IBaseRequest> FRequestFactory::CreateAuthorizedRequest(const FString& Url, ERequestVerb RequestVerb, const FString& Payload, float Timeout) const
{
	TSharedPtr<IBaseRequest> MainRequest = MakeShared<FBaseRequest>(CancellationDelegate, Url, UserData.Token, RequestVerb, Payload, Timeout);
	TSharedPtr<IBaseRequest> RefreshRequest = UserData.bIsExistingUser ? CreateTokenRefreshRequest() : nullptr;
	return MakeShared<FAuthorizedRequest>(MainRequest, RefreshRequest, TokenRefreshedDelegate, SessionExpiredDelegate);
}
