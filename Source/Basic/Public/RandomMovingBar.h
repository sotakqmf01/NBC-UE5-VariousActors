// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomMovingBar.generated.h"

UCLASS()
class BASIC_API ARandomMovingBar : public AActor
{
	GENERATED_BODY()
	
public:	
	ARandomMovingBar();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bar|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bar|Components");
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Speed")
	float SpeedY;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Speed")
	float SpeedZ;
	
	// 축 별 왕복할 시작위치와 끝위치
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Locations")
	float StartLocationY;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Locations")
	float EndLocationY;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Locations")
	float StartLocationZ;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Locations")
	float EndLocationZ;

	// Z축에서 한 번 왕복할 때마다 랜덤한 끝위치를 선택하기위한 랜덤함수의 범위 지정
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Range")
	float MinOfRange;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Range")
	float MaxOfRange;

	float TargetLocationY;
	float TargetLocationZ;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
