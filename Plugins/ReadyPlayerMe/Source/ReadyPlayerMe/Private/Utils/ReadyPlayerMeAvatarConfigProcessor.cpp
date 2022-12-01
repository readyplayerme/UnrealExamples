// Copyright © 2021++ Ready Player Me


#include "Utils/ReadyPlayerMeAvatarConfigProcessor.h"

#include "ReadyPlayerMePluginInfo.h"
#include "ReadyPlayerMeTypes.h"
#include "AvatarConfig/ReadyPlayerMeAvatarConfig.h"
#include "AvatarConfig/ReadyPlayerMeMorphTargetGroup.h"
#include "Kismet/KismetStringLibrary.h"

static const TMap<EAvatarPose, FString> POSE_TO_STRING =
{
	{ EAvatarPose::APose, "A" },
	{ EAvatarPose::TPose, "T" }
};

static const TMap<EAvatarTextureAtlas, FString> TEXTURE_ATLAS_TO_STRING =
{
	{ EAvatarTextureAtlas::None, "none" },
	{ EAvatarTextureAtlas::High, "1024" },
	{ EAvatarTextureAtlas::Medium, "512" },
	{ EAvatarTextureAtlas::Low, "256" }
};

static const TMap<EStandardMorphTargetGroup, FString> MORPH_TARGETS_GROUP_TO_STRING =
{
	{ EStandardMorphTargetGroup::None, "none" },
	{ EStandardMorphTargetGroup::Oculus, "Oculus%20Visemes" },
	{ EStandardMorphTargetGroup::ArKit, "ARKit" }
};

static const TMap<EAvatarMorphTarget, FString> MORPH_TARGETS_TO_STRING =
{
	{ EAvatarMorphTarget::Viseme_aa, "viseme_aa" },
	{ EAvatarMorphTarget::Viseme_E, "viseme_E" },
	{ EAvatarMorphTarget::Viseme_I, "viseme_I" },
	{ EAvatarMorphTarget::Viseme_O, "viseme_O" },
	{ EAvatarMorphTarget::Viseme_U, "viseme_U" },
	{ EAvatarMorphTarget::Viseme_CH, "viseme_CH" },
	{ EAvatarMorphTarget::Viseme_DD, "viseme_DD" },
	{ EAvatarMorphTarget::Viseme_FF, "viseme_FF" },
	{ EAvatarMorphTarget::Viseme_kk, "viseme_kk" },
	{ EAvatarMorphTarget::Viseme_nn, "viseme_nn" },
	{ EAvatarMorphTarget::Viseme_PP, "viseme_PP" },
	{ EAvatarMorphTarget::Viseme_RR, "viseme_RR" },
	{ EAvatarMorphTarget::Viseme_sil, "viseme_sil" },
	{ EAvatarMorphTarget::Viseme_SS, "viseme_SS" },
	{ EAvatarMorphTarget::Viseme_TH, "viseme_TH" },

	{ EAvatarMorphTarget::BrowDownLeft, "browDownLeft" },
	{ EAvatarMorphTarget::BrowDownRight, "browDownRight" },
	{ EAvatarMorphTarget::BrowInnerUp, "browInnerUp" },
	{ EAvatarMorphTarget::BrowOuterUpLeft, "browOuterUpLeft" },
	{ EAvatarMorphTarget::BrowOuterUpRight, "browOuterUpRight" },
	{ EAvatarMorphTarget::EyeBlinkLeft, "eyeBlinkLeft" },
	{ EAvatarMorphTarget::EyeBlinkRight, "eyeBlinkRight" },
	{ EAvatarMorphTarget::EyeSquintLeft, "eyeSquintLeft" },
	{ EAvatarMorphTarget::EyeSquintRight, "eyeSquintRight" },
	{ EAvatarMorphTarget::EyeWideLeft, "eyeWideLeft" },
	{ EAvatarMorphTarget::EyeWideRight, "eyeWideRight" },
	{ EAvatarMorphTarget::JawOpen, "jawOpen" },
	{ EAvatarMorphTarget::JawForward, "jawForward" },
	{ EAvatarMorphTarget::JawLeft, "jawLeft" },
	{ EAvatarMorphTarget::JawRight, "jawRight" },
	{ EAvatarMorphTarget::NoseSneerLeft, "noseSneerLeft" },
	{ EAvatarMorphTarget::NoseSneerRight, "noseSneerRight" },
	{ EAvatarMorphTarget::CheekPuff, "cheekPuff" },
	{ EAvatarMorphTarget::CheekSquintLeft, "cheekSquintLeft" },
	{ EAvatarMorphTarget::CheekSquintRight, "cheekSquintRight" },
	{ EAvatarMorphTarget::MouthSmileLeft, "mouthSmileLeft" },
	{ EAvatarMorphTarget::MouthSmileRight, "mouthSmileRight" },
	{ EAvatarMorphTarget::MouthLeft, "mouthLeft" },
	{ EAvatarMorphTarget::MouthRight, "mouthRight" },
	{ EAvatarMorphTarget::MouthClose, "mouthClose" },
	{ EAvatarMorphTarget::MouthFunnel, "mouthFunnel" },
	{ EAvatarMorphTarget::MouthDimpleLeft, "mouthDimpleLeft" },
	{ EAvatarMorphTarget::MouthDimpleRight, "mouthDimpleRight" },
	{ EAvatarMorphTarget::MouthStretchLeft, "mouthStretchLeft" },
	{ EAvatarMorphTarget::MouthStretchRight, "mouthStretchRight" },
	{ EAvatarMorphTarget::MouthRollLower, "mouthRollLower" },
	{ EAvatarMorphTarget::MouthRollUpper, "mouthRollUpper" },
	{ EAvatarMorphTarget::MouthPressLeft, "mouthPressLeft" },
	{ EAvatarMorphTarget::MouthPressRight, "mouthPressRight" },
	{ EAvatarMorphTarget::MouthUpperUpLeft, "mouthUpperUpLeft" },
	{ EAvatarMorphTarget::MouthUpperUpRight, "mouthUpperUpRight" },
	{ EAvatarMorphTarget::MouthFrownLeft, "mouthFrownLeft" },
	{ EAvatarMorphTarget::MouthFrownRight, "mouthFrownRight" },
	{ EAvatarMorphTarget::MouthPucker, "mouthPucker" },
	{ EAvatarMorphTarget::MouthShrugLower, "mouthShrugLower" },
	{ EAvatarMorphTarget::MouthShrugUpper, "mouthShrugUpper" },
	{ EAvatarMorphTarget::MouthLowerDownLeft, "mouthLowerDownLeft" },
	{ EAvatarMorphTarget::MouthLowerDownRight, "mouthLowerDownRight" },

	{ EAvatarMorphTarget::MouthOpen, "mouthOpen" },
	{ EAvatarMorphTarget::MouthSmile, "mouthSmile" },
	{ EAvatarMorphTarget::EyesClosed, "eyesClosed" },
	{ EAvatarMorphTarget::EyesLookUp, "eyesLookUp" },
	{ EAvatarMorphTarget::EyesLookDown, "eyesLookDown" },

	{ EAvatarMorphTarget::EyeLookDownLeft, "eyeLookDownLeft" },
	{ EAvatarMorphTarget::EyeLookInLeft, "eyeLookInLeft" },
	{ EAvatarMorphTarget::EyeLookOutLeft, "eyeLookOutLeft" },
	{ EAvatarMorphTarget::EyeLookUpLeft, "eyeLookUpLeft" },
	{ EAvatarMorphTarget::EyeLookDownRight, "eyeLookDownRight" },
	{ EAvatarMorphTarget::EyeLookInRight, "eyeLookInRight" },
	{ EAvatarMorphTarget::EyeLookOutRight, "eyeLookOutRight" },
	{ EAvatarMorphTarget::EyeLookUpRight, "eyeLookUpRight" },
	{ EAvatarMorphTarget::TongueOut, "tongueOut" }
};

static const TMap<EAvatarTextureSizeLimit, FString> TEXTURE_SIZE_LIMIT_TO_STRING =
{
	{ EAvatarTextureSizeLimit::Limit_1024, "1024" },
	{ EAvatarTextureSizeLimit::Limit_512, "512" },
	{ EAvatarTextureSizeLimit::Limit_256, "256" }
};

namespace
{
	FString ProcessMorphTargets(const UReadyPlayerMeAvatarConfig* AvatarConfig)
	{
		if (AvatarConfig->MorphTargetGroup == nullptr)
		{
			return "";
		}
		TSet<EAvatarMorphTarget> Targets;
		TSet<EStandardMorphTargetGroup> Groups;
		AvatarConfig->MorphTargetGroup->GetTargets(Groups, Targets);
		if (Targets.Num() == 0 && Groups.Num() == 0)
		{
			return "";
		}
		TArray<FString> Morphs;
		for (const auto& Target : Targets)
		{
			Morphs.Add(MORPH_TARGETS_TO_STRING[Target]);
		}
		for (const auto& Group : Groups)
		{
			Morphs.Add(MORPH_TARGETS_GROUP_TO_STRING[Group]);
		}
		return "morphTargets=" + FString::Join(Morphs, TEXT(","));
	}
}

FString FReadyPlayerMeAvatarConfigProcessor::Process(UReadyPlayerMeAvatarConfig* AvatarConfig)
{
	if (!AvatarConfig)
	{
		return "";
	}
	const bool UseDraco = FReadyPlayerMePluginInfo::IsDracoPluginIncluded() && AvatarConfig->bUseDracoMeshCompression;
	TArray<FString> Parameters;
	Parameters.Add("pose=" + POSE_TO_STRING[AvatarConfig->Pose]);
	Parameters.Add("meshLod=" + FString::FromInt(static_cast<int>(AvatarConfig->MeshLod)));
	Parameters.Add("textureAtlas=" + TEXTURE_ATLAS_TO_STRING[AvatarConfig->TextureAtlas]);
	Parameters.Add("textureSizeLimit=" + TEXTURE_SIZE_LIMIT_TO_STRING[AvatarConfig->TextureSizeLimit]);
	Parameters.Add(ProcessMorphTargets(AvatarConfig));
	Parameters.Add("useHands=" + UKismetStringLibrary::Conv_BoolToString(AvatarConfig->bUseHands));
	Parameters.Add("useDracoMeshCompression=" + UKismetStringLibrary::Conv_BoolToString(UseDraco));
	return "?" + FString::Join(Parameters, TEXT("&"));
}
