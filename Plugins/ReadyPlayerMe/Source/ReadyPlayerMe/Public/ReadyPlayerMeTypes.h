// Copyright © 2024 Ready Player Me
#pragma once

#include "ReadyPlayerMeTypes.generated.h"

UENUM(BlueprintType)
enum class EAvatarGender : uint8
{
	Undefined UMETA(DisplayName = "Gender Undefined"),
	Masculine UMETA(DisplayName = "Gender Masculine"),
	Feminine UMETA(DisplayName = "Gender Feminine")
};

UENUM(BlueprintType)
enum class EAvatarBodyType : uint8
{
	Undefined UMETA(DisplayName = "Undefined Body Type"),
	FullBody UMETA(DisplayName = "Full Body Type"),
	HalfBody UMETA(DisplayName = "Half Body Type")
};

USTRUCT(BlueprintType)
struct FAvatarMetadata
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	EAvatarBodyType BodyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	EAvatarGender OutfitGender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	FString SkinTone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	FString UpdatedAtDate;

	FAvatarMetadata()
	{
		BodyType = EAvatarBodyType::Undefined;
		OutfitGender = EAvatarGender::Undefined;
	}
};

UENUM(BlueprintType)
enum class EStandardMorphTargetGroup : uint8
{
	None UMETA(DisplayName = "None"),
	ArKit UMETA(DisplayName = "ArKit"),
	Oculus UMETA(DisplayName = "Oculus Viseme")
};

UENUM(BlueprintType)
enum class EAvatarMorphTarget : uint8
{
	// Oculus Viseme blend shapes
	Viseme_aa UMETA(DisplayName = "Viseme_aa"),
	Viseme_E UMETA(DisplayName = "Viseme_E"),
	Viseme_I UMETA(DisplayName = "Viseme_I"),
	Viseme_O UMETA(DisplayName = "Viseme_O"),
	Viseme_U UMETA(DisplayName = "Viseme_U"),
	Viseme_CH UMETA(DisplayName = "Viseme_CH"),
	Viseme_DD UMETA(DisplayName = "Viseme_DD"),
	Viseme_FF UMETA(DisplayName = "Viseme_FF"),
	Viseme_kk UMETA(DisplayName = "Viseme_kk"),
	Viseme_nn UMETA(DisplayName = "Viseme_nn"),
	Viseme_PP UMETA(DisplayName = "Viseme_PP"),
	Viseme_RR UMETA(DisplayName = "Viseme_RR"),
	Viseme_sil UMETA(DisplayName = "Viseme_sil"),
	Viseme_SS UMETA(DisplayName = "Viseme_SS"),
	Viseme_TH UMETA(DisplayName = "Viseme_TH"),

	// ArKit blend shapes
	BrowDownLeft UMETA(DisplayName = "BrowDownLeft"),
	BrowDownRight UMETA(DisplayName = "BrowDownRight"),
	BrowInnerUp UMETA(DisplayName = "BrowInnerUp"),
	BrowOuterUpLeft UMETA(DisplayName = "BrowOuterUpLeft"),
	BrowOuterUpRight UMETA(DisplayName = "BrowOuterUpRight"),
	EyeBlinkLeft UMETA(DisplayName = "EyeBlinkLeft"),
	EyeBlinkRight UMETA(DisplayName = "EyeBlinkRight"),
	EyeSquintLeft UMETA(DisplayName = "EyeSquintLeft"),
	EyeSquintRight UMETA(DisplayName = "EyeSquintRight"),
	EyeWideLeft UMETA(DisplayName = "EyeWideLeft"),
	EyeWideRight UMETA(DisplayName = "EyeWideRight"),
	JawOpen UMETA(DisplayName = "JawOpen"),
	JawForward UMETA(DisplayName = "JawForward"),
	JawLeft UMETA(DisplayName = "JawLeft"),
	JawRight UMETA(DisplayName = "JawRight"),
	NoseSneerLeft UMETA(DisplayName = "NoseSneerLeft"),
	NoseSneerRight UMETA(DisplayName = "NoseSneerRight"),
	CheekPuff UMETA(DisplayName = "CheekPuff"),
	CheekSquintLeft UMETA(DisplayName = "CheekSquintLeft"),
	CheekSquintRight UMETA(DisplayName = "CheekSquintRight"),
	MouthSmileLeft UMETA(DisplayName = "MouthSmileLeft"),
	MouthSmileRight UMETA(DisplayName = "MouthSmileRight"),
	MouthLeft UMETA(DisplayName = "MouthLeft"),
	MouthRight UMETA(DisplayName = "MouthRight"),
	MouthClose UMETA(DisplayName = "MouthClose"),
	MouthFunnel UMETA(DisplayName = "MouthFunnel"),
	MouthDimpleLeft UMETA(DisplayName = "MouthDimpleLeft"),
	MouthDimpleRight UMETA(DisplayName = "MouthDimpleRight"),
	MouthStretchLeft UMETA(DisplayName = "MouthStretchLeft"),
	MouthStretchRight UMETA(DisplayName = "MouthStretchRight"),
	MouthRollLower UMETA(DisplayName = "MouthRollLower"),
	MouthRollUpper UMETA(DisplayName = "MouthRollUpper"),
	MouthPressLeft UMETA(DisplayName = "MouthPressLeft"),
	MouthPressRight UMETA(DisplayName = "MouthPressRight"),
	MouthUpperUpLeft UMETA(DisplayName = "MouthUpperUpLeft"),
	MouthUpperUpRight UMETA(DisplayName = "MouthUpperUpRight"),
	MouthFrownLeft UMETA(DisplayName = "MouthFrownLeft"),
	MouthFrownRight UMETA(DisplayName = "MouthFrownRight"),
	MouthPucker UMETA(DisplayName = "MouthPucker"),
	MouthShrugLower UMETA(DisplayName = "MouthShrugLower"),
	MouthShrugUpper UMETA(DisplayName = "MouthShrugUpper"),
	MouthLowerDownLeft UMETA(DisplayName = "MouthLowerDownLeft"),
	MouthLowerDownRight UMETA(DisplayName = "MouthLowerDownRight"),

	// Additional blend shapes
	MouthOpen UMETA(DisplayName = "MouthOpen"),
	MouthSmile UMETA(DisplayName = "MouthSmile"),
	EyesClosed UMETA(DisplayName = "EyesClosed"),
	EyesLookUp UMETA(DisplayName = "EyesLookUp"),
	EyesLookDown UMETA(DisplayName = "EyesLookDown"),

	EyeLookDownLeft UMETA(DisplayName = "EyeLookDownLeft"),
	EyeLookInLeft UMETA(DisplayName = "EyeLookInLeft"),
	EyeLookOutLeft UMETA(DisplayName = "EyeLookOutLeft"),
	EyeLookUpLeft UMETA(DisplayName = "EyeLookUpLeft"),
	EyeLookDownRight UMETA(DisplayName = "EyeLookDownRight"),
	EyeLookInRight UMETA(DisplayName = "EyeLookInRight"),
	EyeLookOutRight UMETA(DisplayName = "EyeLookOutRight"),
	EyeLookUpRight UMETA(DisplayName = "EyeLookUpRight"),
	TongueOut UMETA(DisplayName = "TongueOut"),
};

UENUM(BlueprintType)
enum class ERpmRenderExpression : uint8
{
	None,
	Happy,
	Lol,
	Sad,
	Scared,
	Rage
};

UENUM(BlueprintType)
enum class ERpmRenderPose : uint8
{
	PowerStance,
	Relaxed,
	Standing,
	ThumbsUp
};

UENUM(BlueprintType)
enum class ERpmRenderCamera : uint8
{
	Portrait,
	FullBody
};

USTRUCT(BlueprintType)
struct FRpmAvatarRenderProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	ERpmRenderCamera Camera = ERpmRenderCamera::Portrait;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	ERpmRenderPose Pose = ERpmRenderPose::Relaxed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	ERpmRenderExpression Expression = ERpmRenderExpression::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	bool bIsTransparent = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe", meta = (ToolTip = "Applies only to the non transparent images"))
	FColor Background = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe", meta=(UIMin=0, UIMax=100, ClampMin=0, ClampMax=100, ToolTip = "Applies only to the non transparent images"))
	int32 Quality = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe", meta=(UIMin=1, UIMax=1024, ClampMin=1, ClampMax=1024))
	int32 Size = 800;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	TMap<EAvatarMorphTarget, float> BlendShapes;
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAvatarDownloadCompleted, class USkeletalMesh*, Mesh, const FAvatarMetadata&, Metadata);

DECLARE_DYNAMIC_DELEGATE(FAvatarLoadCompleted);

DECLARE_DYNAMIC_DELEGATE_OneParam(FAvatarLoadFailed, const FString&, ErrorMessage);

DECLARE_DYNAMIC_DELEGATE_OneParam(FDownloadImageFailed, const FString&, ErrorMessage);

DECLARE_DYNAMIC_DELEGATE_OneParam(FGlbLoadCompleted, class USkeletalMesh*, SkeletalMesh);

struct FAvatarUri
{
	FString Guid;
	FString ModelUrl;
	TArray<FString> ModelLodUrls;
	FString LocalModelPath;
	TArray<FString> LocalModelLodPaths;
	FString MetadataUrl;
	FString LocalMetadataPath;
	FString LocalAvatarDirectory;
};

DECLARE_LOG_CATEGORY_EXTERN(LogReadyPlayerMe, Log, All);
