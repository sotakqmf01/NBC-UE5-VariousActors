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
	
	// Ä¸½¶ ÄÝ¸®Àü ÄÄÆ÷³ÍÆ®(Root Component)
	UCapsuleComponent* CapsuleRoot;

	// ½ºÄÌ·¹Å» ¸Þ½Ã
	USkeletalMeshComponent* SkeletalMeshComp;

	// ¿Àµð¿À ÄÄÆ÷³ÍÆ®
	UAudioComponent* AudioComp;
	
	// ½ºÇÁ¸µ ¾Ï
	USpringArmComponent* SpringArmComp;

	// Ä«¸Þ¶ó
	UCameraComponent* CameraComp;
};
