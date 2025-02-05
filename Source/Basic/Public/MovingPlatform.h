// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class BASIC_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingPlatform();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Platform|Components");
	USceneComponent* SceneRoot;
	// ����ƽ �޽� ���� ��𼭳� �����Ӱ�
	UPROPERTY(EditAnywhere, Category = "Platform|Components")
	UStaticMeshComponent* StaticMeshComp;

	// �ν��Ͻ����� �����Ϳ��� ���� �� ���� ����
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Platform|Properties")
	FVector StartLocation;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Platform|Properties")
	float SpeedY;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Platform|Properties")
	float DistanceLimit;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Platform|Properties")
	float PausedDuration;
	// �����Ϳ��� �������� ����
	float Distance;
	bool bIsPaused;
	FTimerHandle PauseTimerHandle;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void ResumeMovement();

};
