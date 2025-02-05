// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PotionSpawner.generated.h"

class ASpawnedPotion;

UCLASS()
class BASIC_API APotionSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	APotionSpawner();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Components")
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|SpawnedItem")
	ASpawnedPotion* SpawnedPotion;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Properties")
	//float PotionLifeTime;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Properties")
	//float PotionDeleteDelay;

	virtual void BeginPlay() override;

	void SpawnActor();
	void DespawnActor();

};
