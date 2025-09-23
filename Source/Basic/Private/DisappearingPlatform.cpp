// Fill out your copyright notice in the Description page of Project Settings.


#include "DisappearingPlatform.h"

ADisappearingPlatform::ADisappearingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(SceneRoot);
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/Floor_400x400.Floor_400x400"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	StaticMeshComp->SetRelativeLocation(FVector(-100.0f, -100.0f, 0.0f));
	StaticMeshComp->SetRelativeScale3D(FVector(0.5f));

	StartLocation = FVector::ZeroVector;
	InvisibleTime = 3.0f;
	VisibleTime = 5.0f;
	TotalDeltaTime = 0.0f;
	bIsInvisible = false;
}

void ADisappearingPlatform::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(StartLocation);
}

void ADisappearingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsInvisible)
	{
		return;
	}

	TotalDeltaTime += DeltaTime;

	if (TotalDeltaTime >= VisibleTime)
	{
		bIsInvisible = true;
		// 액터를 숨기려면 인자로 true를 넣어야함
		SetActorHiddenInGame(bIsInvisible);

		GetWorld()->GetTimerManager().SetTimer(VisibleTimerHandle, this, &ADisappearingPlatform::ChangeVisibility, InvisibleTime);
	}
}

void ADisappearingPlatform::ChangeVisibility()
{
	TotalDeltaTime = 0.0f;
	bIsInvisible = false;
	// 액터를 숨기려면 인자로 false를 넣어야함
	SetActorHiddenInGame(bIsInvisible);
}