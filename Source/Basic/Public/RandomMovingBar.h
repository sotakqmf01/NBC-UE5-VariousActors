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
	
	// �� �� �պ��� ������ġ�� ����ġ
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Locations")
	float StartLocationY;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Locations")
	float EndLocationY;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Locations")
	float StartLocationZ;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Locations")
	float EndLocationZ;

	// Z�࿡�� �� �� �պ��� ������ ������ ����ġ�� �����ϱ����� �����Լ��� ���� ����
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Range")
	float MinOfRange;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bar|Properties|Range")
	float MaxOfRange;

	float TargetLocationY;
	float TargetLocationZ;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
