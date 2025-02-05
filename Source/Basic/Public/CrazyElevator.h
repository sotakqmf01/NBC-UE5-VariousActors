// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrazyElevator.generated.h"

UCLASS()
class BASIC_API ACrazyElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrazyElevator();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Components")
	UStaticMeshComponent* StaticMeshComp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator|Properties")
	//float TotalDeltaTime = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator|Properties")
	float Distance = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Properties")
	float SpeedZ = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Properties")
	float RotationSpeed = 90.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Properties")
	FVector StartLocation;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Elevator|Actions")
	void ResetActorPosition();
	UFUNCTION(BlueprintPure, Category = "Elevator|Properties")
	float GetRotationSpeed() const;

};
