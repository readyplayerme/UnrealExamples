// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "ReadyPlayerMeComponent.h"

AReadyPlayerMeActor::AReadyPlayerMeActor()
{
	// Set this actor not to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = false;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(SkeletalMeshComponent);

	ReadyPlayerMeComponent = CreateDefaultSubobject<UReadyPlayerMeComponent>(TEXT("ReadyPlayerMe"));
	SkeletalMeshComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
}
