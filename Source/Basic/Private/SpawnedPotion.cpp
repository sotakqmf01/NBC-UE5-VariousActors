// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnedPotion.h"

ASpawnedPotion::ASpawnedPotion()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(SceneRoot);
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Potion_A.SM_Potion_A"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	StaticMeshComp->SetRelativeRotation(FRotator(5.f, 0.f, 0.f));

	RotationSpeed = 90.0f;

}

void ASpawnedPotion::BeginPlay()
{
	Super::BeginPlay();

	//SetLifeSpan(5.0f);
}

void ASpawnedPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorWorldRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}
}