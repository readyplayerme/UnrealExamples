// Copyright © 2024 Ready Player Me


#include "ReadyPlayerMeLoadRenderAction.h"

#include "Kismet/KismetRenderingLibrary.h"
#include "Utils/RenderUrlConvertor.h"
#include "Request/AvatarRequest.h"

//TODO: Move the timout to the RPMSettings to make it configurable
constexpr float IMAGE_REQUEST_TIMEOUT = 60.f;

UReadyPlayerMeLoadRenderAction* UReadyPlayerMeLoadRenderAction::LoadAvatarRenderAsync(const FString& Url, const FRpmAvatarRenderProperties& Properties)
{
	UReadyPlayerMeLoadRenderAction* Action = NewObject<UReadyPlayerMeLoadRenderAction>();
	Action->Load(Url, Properties);
	return Action;
}

void UReadyPlayerMeLoadRenderAction::Load(const FString& Url, const FRpmAvatarRenderProperties& Properties)
{
#if !UE_SERVER
	const FString ImageUrl = FRenderUrlConvertor::CreateRenderUrl(Url, Properties);
	ImageRequest = MakeShared<FAvatarRequest>();
	ImageRequest->GetCompleteCallback().BindUObject(this, &UReadyPlayerMeLoadRenderAction::OnImageDownloaded);
	ImageRequest->Download(ImageUrl, IMAGE_REQUEST_TIMEOUT);
#endif
}

void UReadyPlayerMeLoadRenderAction::OnImageDownloaded(bool bSuccess)
{
	if (!OnCompleted.IsBound())
	{
		return;
	}
	if (bSuccess)
	{
		UTexture2D* Texture = UKismetRenderingLibrary::ImportBufferAsTexture2D(this, ImageRequest->GetContent());
		OnCompleted.Broadcast(Texture);
	}
	else
	{
		OnFailed.Broadcast(nullptr);
	}
	ImageRequest.Reset();
}

void UReadyPlayerMeLoadRenderAction::BeginDestroy()
{
	if (ImageRequest.IsValid())
	{
		OnCompleted.Clear();
		OnFailed.Clear();
		ImageRequest->CancelRequest();
		ImageRequest.Reset();
	}

	Super::BeginDestroy();
}
