// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomLocationSpawner.generated.h"

class UBoxComponent;
class AItem;

UCLASS()
class BASIC_API ARandomLocationSpawner : public AActor
{
	GENERATED_BODY()

public:
	ARandomLocationSpawner();

protected:
	USceneComponent* SceneRoot;
	UBoxComponent* SpawnVolume;

	// 스폰한 액터들의 위치를 담을 배열
	TSet<AItem*> ItemSet;

	// 일정 범위, 이 범위 안에서 랜덤하게 액터 스폰
	float XAxisMin;
	float XAxisMax;
	float YAxisMin;
	float YAxisMax;
	float ZAxis;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SpawnActor();
	void OrganizeSet();
};