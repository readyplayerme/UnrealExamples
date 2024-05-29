// Copyright © 2024 Ready Player Me


#include "RenderUrlConvertor.h"
#include "AvatarUrlConvertor.h"
#include "MorphTargetUtils.h"
#include "Misc/Paths.h"

static const TMap<ERpmRenderExpression,FString> EXPRESSION_TO_STRING_MAP =
{
	{ERpmRenderExpression::Happy, "happy"},
	{ERpmRenderExpression::Lol, "lol"},
	{ERpmRenderExpression::Sad, "sad"},
	{ERpmRenderExpression::Scared, "scared"},
	{ERpmRenderExpression::Rage, "rage"}
};

static const TMap<ERpmRenderPose,FString> POSE_TO_STRING_MAP =
{
	{ERpmRenderPose::Relaxed, "relaxed"},
	{ERpmRenderPose::PowerStance, "power-stance"},
	{ERpmRenderPose::Standing, "standing"},
	{ERpmRenderPose::ThumbsUp, "thumbs-up"}
};

static const TMap<ERpmRenderCamera,FString> CAMERA_TO_STRING_MAP =
{
	{ERpmRenderCamera::Portrait, "portrait"},
	{ERpmRenderCamera::FullBody, "fullbody"}
};

FString FRenderUrlConvertor::CreateRenderUrl(const FString& Url, const FRpmAvatarRenderProperties& Properties)
{
	const FString ValidUrl = FAvatarUrlConvertor::GetValidatedUrl(Url);
	FString UrlLink, UrlQueryString;
	if (!ValidUrl.Split(TEXT("?"), &UrlLink, &UrlQueryString))
	{
		UrlLink = ValidUrl;
	}
	FString Path, Guid, Extension;
	FPaths::Split(UrlLink, Path, Guid, Extension);

	TArray<FString> Parameters;
	Parameters.Add("camera=" + CAMERA_TO_STRING_MAP[Properties.Camera]);
	Parameters.Add("pose=" + POSE_TO_STRING_MAP[Properties.Pose]);
	if (Properties.Expression != ERpmRenderExpression::None)
	{
		Parameters.Add("expression=" + EXPRESSION_TO_STRING_MAP[Properties.Expression]);
	}
	for (const auto& BlendShape : Properties.BlendShapes)
	{
		const FString KeyStr = FMorphTargetUtils::MorphTargetToString(BlendShape.Key);
		Parameters.Add(FString::Format(TEXT("blendShapes[{0}]={1}"), {KeyStr, FString::SanitizeFloat(BlendShape.Value)}));
	}
	if (!Properties.bIsTransparent)
	{
		Parameters.Add(FString::Format(TEXT("background={0},{1},{2}"),
		{FString::FromInt(Properties.Background.R), FString::FromInt(Properties.Background.G), FString::FromInt(Properties.Background.B)}));
		Parameters.Add("quality=" + FString::FromInt(Properties.Quality));
	}
	Parameters.Add("size=" + FString::FromInt(Properties.Size));
	const FString ExtensionStr = Properties.bIsTransparent ? "png" : "jpg";

	const FString RenderUrl = FString::Format(TEXT("{0}/{1}.{2}?{3}"),
		{Path, Guid, ExtensionStr, FString::Join(Parameters, TEXT("&"))});
	
	return RenderUrl;
}
