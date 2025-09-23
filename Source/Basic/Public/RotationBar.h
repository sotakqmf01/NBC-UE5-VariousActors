// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotationBar.generated.h"

UCLASS()
class BASIC_API ARotationBar : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARotationBar();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Bar|Components")
	USceneComponent* SceneRoot;
	// 스태틱 메시 에디터에서 변경 불가능
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bar|Components")
	UStaticMeshComponent* StaticMeshComp;

	// 모든 변수는 인스턴스들만 변경 가능
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties");
	FVector SettingLocation;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties");
	float RotationSpeed = 90.0f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};