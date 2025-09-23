// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationBar.h"

ARotationBar::ARotationBar()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(SceneRoot);
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_PillarFrame300.SM_PillarFrame300"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	StaticMeshComp->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	StaticMeshComp->SetRelativeScale3D(FVector(1.0f, 1.0f, 3.1f));

	SettingLocation = FVector::ZeroVector;
}

void ARotationBar::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(SettingLocation);
}

void ARotationBar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = GetActorRotation() + FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f);
	SetActorRotation(NewRotation);
}