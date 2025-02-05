// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
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

	// default �⺻ ��ġ�� (0,0,0), �����Ϳ��� ���� ����
	StartLocation = FVector::ZeroVector;
	SpeedY = 750.0f;
	DistanceLimit = 1000.0f;
	Distance = 0.0f;

	bIsPaused = false;
	PausedDuration = 2.0f;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(StartLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �����ִ� ���¸� �ƹ��͵� ���ϰ� �ٷ� return
	if (bIsPaused)
	{
		return;
	}

	// y�� �������� �����̱�
	AddActorWorldOffset(FVector(0.0f, SpeedY * DeltaTime, 0.0f));
	Distance += SpeedY * DeltaTime;

	// ���� ���� �Ÿ��� �̵������� ��ġ �����ϰ� ��� ����
	if (FMath::Abs(Distance) >= DistanceLimit)
	{
		bIsPaused = true;

		if (SpeedY > 0)
		{
			SetActorLocation(StartLocation + FVector(0.0f, DistanceLimit, 0.0f));
		}
		else
		{
			SetActorLocation(StartLocation);
		}

		// GetWorldTimerManager() = GetWorld()->GetTimerManager()
		GetWorld()->GetTimerManager().SetTimer(PauseTimerHandle, this, &AMovingPlatform::ResumeMovement, PausedDuration, false);
	}
}

void AMovingPlatform::ResumeMovement()
{
	bIsPaused = false;
	SpeedY *= -1;
	Distance = 0.0f;
}