// Copyright © 2021++ Ready Player Me


#include "Utils/ReadyPlayerMeRenderRequestParams.h"

#include "glTFRuntimeAsset.h"
#include "Templates/SharedPointer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Policies/CondensedJsonPrintPolicy.h"

static const FString JSON_MODEL = "model";
static const FString JSON_SCENE = "scene";
static const FString JSON_ARMATURE = "armature";

static const FString JSON_ARMATURE_TARGET_FEMALE = "ArmatureTargetFemale";
static const FString JSON_ARMATURE_TARGET_MALE = "ArmatureTargetMale";

static const TMap<ERenderSceneType,FString> SCENE_TYPE_TO_STRING_MAP =
{
	{ERenderSceneType::FullBodyPortrait, "fullbody-portrait-v1"},
	{ERenderSceneType::HalfBodyPortrait, "halfbody-portrait-v1"},
	{ERenderSceneType::FullBodyPortraitTransparent, "fullbody-portrait-v1-transparent"},
	{ERenderSceneType::HalfBodyPortraitTransparent, "halfbody-portrait-v1-transparent"},
	{ERenderSceneType::FullBodyPostureTransparent, "fullbody-posture-v1-transparent"}
};

FString FReadyPlayerMeRenderRequestParams::SceneTypeToString(const ERenderSceneType& SceneType)
{
	if (SCENE_TYPE_TO_STRING_MAP.Contains(SceneType))
	{
		return SCENE_TYPE_TO_STRING_MAP[SceneType];
	}
	else
	{
		UE_LOG(LogReadyPlayerMe, Warning, TEXT("Undefined Render Scene Type"));
		return SCENE_TYPE_TO_STRING_MAP[ERenderSceneType::HalfBodyPortrait];
	}
}

FString FReadyPlayerMeRenderRequestParams::GetArmatureTarget(const EAvatarGender& Gender)
{
	if (Gender == EAvatarGender::Feminine)
	{
		return JSON_ARMATURE_TARGET_FEMALE;
	}
	else if (Gender == EAvatarGender::Masculine)
	{
		return JSON_ARMATURE_TARGET_MALE;
	}
	return "";
}

FString FReadyPlayerMeRenderRequestParams::SerializeRenderRequestContent(const FString& ModelUrl, const ERenderSceneType& SceneType, const EAvatarGender& Gender)
{
	const TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();

	JsonObject->SetStringField(JSON_MODEL, ModelUrl);
	JsonObject->SetStringField(JSON_SCENE, SceneTypeToString(SceneType));
	JsonObject->SetStringField(JSON_ARMATURE, GetArmatureTarget(Gender));

	FString JsonString;
	const auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonString);
	if (!FJsonSerializer::Serialize(JsonObject, Writer))
	{
		UE_LOG(LogReadyPlayerMe, Warning, TEXT("Failed to create a valid url"));
	}
	return JsonString;
}

FString FReadyPlayerMeRenderRequestParams::ExtractUrlFromRenderResponse(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	FString Url;

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{	
		if (JsonObject->HasField("renders"))
		{
			const auto RendersJson = JsonObject->GetArrayField("renders");
			if (RendersJson.Num() != 0)
			{
				Url = RendersJson[0]->AsString();
			}
		}
	}

	return Url;
}
