// Copyright © 2024 Ready Player Me


#include "MorphTargetUtils.h"

static const TMap<EAvatarMorphTarget, FString> ALL_MORPH_TARGETS_TO_STRING =
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

static const TMap<EStandardMorphTargetGroup, FString> ALL_GROUP_TO_STRING =
{
	{ EStandardMorphTargetGroup::None, "none" },
	{ EStandardMorphTargetGroup::Oculus, "Oculus%20Visemes" },
	{ EStandardMorphTargetGroup::ArKit, "ARKit" }
};

FString FMorphTargetUtils::MorphTargetToString(EAvatarMorphTarget MorphTarget)
{
	return  ALL_MORPH_TARGETS_TO_STRING[MorphTarget];
}

FString FMorphTargetUtils::MorphTargetGroupToString(EStandardMorphTargetGroup Group)
{
	return  ALL_GROUP_TO_STRING[Group];
}
