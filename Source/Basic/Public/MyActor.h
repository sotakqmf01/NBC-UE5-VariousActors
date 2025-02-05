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
	
	// ĸ�� �ݸ��� ������Ʈ(Root Component)
	UCapsuleComponent* CapsuleRoot;

	// ���̷�Ż �޽�
	USkeletalMeshComponent* SkeletalMeshComp;

	// ����� ������Ʈ
	UAudioComponent* AudioComp;
	
	// ������ ��
	USpringArmComponent* SpringArmComp;

	// ī�޶�
	UCameraComponent* CameraComp;
};
