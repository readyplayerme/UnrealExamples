// Copyright © 2023++ Ready Player Me


#include "RpmAuthManager.h"
#include "Extractors/UserDataExtractor.h"
#include "Requests/RequestFactory.h"
#include "RpmUserDataSaveGame.h"
#include "Kismet/GameplayStatics.h"

static const FString USER_DATA_SLOT = "RpmUserDataSlot";

FRpmAuthManager::FRpmAuthManager(TSharedPtr<FRequestFactory> RequestFactory)
	: RequestFactory(RequestFactory)
{
}

void FRpmAuthManager::BindTokenRefreshDelegate()
{
	OnTokenRefreshed.BindSP(AsShared(), &FRpmAuthManager::TokenRefreshed);
	RequestFactory->SetTokenRefreshedDelegate(OnTokenRefreshed);
}

void FRpmAuthManager::Logout()
{
	UGameplayStatics::DeleteGameInSlot(USER_DATA_SLOT, 0);
	UserData = {};
	RequestFactory->SetUserData({});
}

void FRpmAuthManager::AuthStart(const FString& Email, bool bIsTypeCode, const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed)
{
	OnAuthenticationCompleted = Completed;
	OnAvatarCreatorFailed = Failed;

	AuthRequest = RequestFactory->CreateAuthStartRequest(FUserDataExtractor::MakeAuthStartPayload(Email, UserData.Id, bIsTypeCode));
	AuthRequest->GetCompleteCallback().BindSP(AsShared(), &FRpmAuthManager::AuthStartCompleted);
	AuthRequest->Download();
}

void FRpmAuthManager::ConfirmActivationCode(const FString& Code, const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed)
{
	OnAuthenticationCompleted = Completed;
	OnAvatarCreatorFailed = Failed;

	AuthRequest = RequestFactory->CreateConfirmCodeRequest(FUserDataExtractor::MakeConfirmCodePayload(Code));
	AuthRequest->GetCompleteCallback().BindSP(AsShared(), &FRpmAuthManager::ConfirmActivationCodeCompleted);
	AuthRequest->Download();
}

void FRpmAuthManager::AuthAnonymous(const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed)
{
	OnAuthenticationCompleted = Completed;
	OnAvatarCreatorFailed = Failed;

	AuthRequest = RequestFactory->CreateAuthAnonymousRequest();
	AuthRequest->GetCompleteCallback().BindSP(AsShared(), &FRpmAuthManager::AuthAnonymousCompleted);
	AuthRequest->Download();
}

void FRpmAuthManager::ConfirmActivationCodeCompleted(bool bSuccess)
{
	if (!bSuccess)
	{
		(void)OnAvatarCreatorFailed.ExecuteIfBound(ERpmAvatarCreatorError::ConfirmActivationCodeFailure);
		return;
	}
	UserData = FUserDataExtractor::ExtractUserData(AuthRequest->GetContentAsString());
	UserData.AppId = RequestFactory->GetAppId();
	UserData.Subdomain = RequestFactory->GetSubdomain();
	RequestFactory->SetUserData(UserData);
	SaveUserData();
	(void)OnAuthenticationCompleted.ExecuteIfBound();
}

void FRpmAuthManager::AuthStartCompleted(bool bSuccess)
{
	if (!bSuccess)
	{
		(void)OnAvatarCreatorFailed.ExecuteIfBound(ERpmAvatarCreatorError::SendActivationCodeFailure);
		return;
	}
	(void)OnAuthenticationCompleted.ExecuteIfBound();
}

void FRpmAuthManager::AuthAnonymousCompleted(bool bSuccess)
{
	if (bSuccess)
	{
		UserData = FUserDataExtractor::ExtractAnonymousUserData(AuthRequest->GetContentAsString());
		UserData.AppId = RequestFactory->GetAppId();
		UserData.Subdomain = RequestFactory->GetSubdomain();
	}
	bSuccess &= UserData.bIsAuthenticated;

	if (!bSuccess)
	{
		(void)OnAvatarCreatorFailed.ExecuteIfBound(ERpmAvatarCreatorError::AuthenticationFailure);
		return;
	}
	RequestFactory->SetUserData(UserData);
	SaveUserData();
	(void)OnAuthenticationCompleted.ExecuteIfBound();
}

void FRpmAuthManager::SaveUserData() const
{
	URpmUserDataSaveGame* SaveGame = Cast<URpmUserDataSaveGame>(UGameplayStatics::CreateSaveGameObject(URpmUserDataSaveGame::StaticClass()));
	if (SaveGame)
	{
		SaveGame->UserData = UserData;
		if (!UGameplayStatics::SaveGameToSlot(SaveGame, USER_DATA_SLOT, 0))
		{
			UE_LOG(LogRpmAvatarCreator, Warning, TEXT("Failed to save user data"));
		}
	}
}

void FRpmAuthManager::LoadUserData()
{
	const URpmUserDataSaveGame* SaveGame = Cast<URpmUserDataSaveGame>(UGameplayStatics::LoadGameFromSlot(USER_DATA_SLOT, 0));
	if (SaveGame)
	{
		if (SaveGame->UserData.AppId != RequestFactory->GetAppId() || SaveGame->UserData.Subdomain != RequestFactory->GetSubdomain())
		{
			UGameplayStatics::DeleteGameInSlot(USER_DATA_SLOT, 0);
		}
		else
		{
			UserData = SaveGame->UserData;
			RequestFactory->SetUserData(UserData);
		}
	}
}

void FRpmAuthManager::TokenRefreshed(const FString& Token, const FString& RefreshToken)
{
	UserData.Token = Token;
	UserData.RefreshToken = RefreshToken;
	RequestFactory->SetUserData(UserData);
	SaveUserData();
}

FRpmUserData FRpmAuthManager::GetUserData() const
{
	return UserData;
}
