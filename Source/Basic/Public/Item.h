// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUnreal, Warning, All);

UCLASS()
class BASIC_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	//FVector ItemLocation;
	//FRotator ItemRotation;
	float RotationSpeed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
