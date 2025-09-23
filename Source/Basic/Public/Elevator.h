// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

UCLASS()
class BASIC_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	AElevator();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Elevator|Properties");
	float SpeedZ;
	//float InterSpeedZ;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Elevator|Properties");
	FVector StartLocation;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Elevator|Properties");
	FVector EndLocation;

	FVector CurrentLocation;
	FVector CurrentTarget;

	bool bIsPaused;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void ResumeMovement();
};
