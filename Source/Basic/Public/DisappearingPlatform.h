// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DisappearingPlatform.generated.h"

UCLASS()
class BASIC_API ADisappearingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ADisappearingPlatform();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Platform|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, Category = "Platform|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Properties")
	FVector StartLocation;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Platform|Properties")
	float InvisibleTime;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Platform|Properties")
	float VisibleTime;

	float TotalDeltaTime;
	bool bIsInvisible;

	FTimerHandle VisibleTimerHandle;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void ChangeVisibility();
};
