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
	// 스태틱 메시 선택 어디서나 자유롭게
	UPROPERTY(EditAnywhere, Category = "Platform|Components")
	UStaticMeshComponent* StaticMeshComp;

	// 인스턴스들은 에디터에서 변수 값 변경 가능
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Platform|Properties")
	FVector StartLocation;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Platform|Properties")
	float SpeedY;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Platform|Properties")
	float DistanceLimit;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Platform|Properties")
	float PausedDuration;
	// 에디터에서 보여주지 않음
	float Distance;
	bool bIsPaused;
	FTimerHandle PauseTimerHandle;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void ResumeMovement();

};
