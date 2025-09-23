// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnedPotion.generated.h"

UCLASS()
class BASIC_API ASpawnedPotion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnedPotion();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion|Components")
	UStaticMeshComponent* StaticMeshComp;

	float RotationSpeed;


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
