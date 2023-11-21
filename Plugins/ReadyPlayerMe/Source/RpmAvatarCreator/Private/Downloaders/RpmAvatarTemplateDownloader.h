// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"

class FRpmAvatarTemplateDownloader : public TSharedFromThis<FRpmAvatarTemplateDownloader>
{
public:
	FRpmAvatarTemplateDownloader(TSharedPtr<class FRequestFactory> Factory);

	void DownloadTemplates(const FAvatarTemplatesDownloadCompleted& DownloadCompleted, const FAvatarCreatorFailed& Failed);
	TArray<FRpmAvatarTemplate> GetAvatarTemplates() const;

private:
	void OnTemplatesDownloadCompleted(bool bSuccess);

	FAvatarTemplatesDownloadCompleted OnDownloadCompleted;
	FAvatarCreatorFailed OnFailed;

	TSharedPtr<class FRequestFactory> RequestFactory;
	TArray<FRpmAvatarTemplate> AvatarTemplates;
	TSharedPtr<class IBaseRequest> AvatarTemplatesRequest;
};
