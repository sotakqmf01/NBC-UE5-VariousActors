#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyActor.generated.h"

UCLASS()
class BASIC_API AMyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActor();

protected:
	//USceneComponent* SceneRoot;

	// 캡슐 콜리전 컴포넌트(Root Component)
	UCapsuleComponent* CapsuleRoot;

	// 스켈레탈 메시
	USkeletalMeshComponent* SkeletalMeshComp;

	// 오디오 컴포넌트
	UAudioComponent* AudioComp;

	// 스프링 암
	USpringArmComponent* SpringArmComp;

	// 카메라
	UCameraComponent* CameraComp;
};