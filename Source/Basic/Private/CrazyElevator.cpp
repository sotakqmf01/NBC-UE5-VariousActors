// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyElevator.h"


ACrazyElevator::ACrazyElevator()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(SceneRoot);
	StaticMeshComp->SetupAttachment(SceneRoot);

	StaticMeshComp->SetRelativeLocation(FVector(-100.f, -100.f, 0.f));
	StaticMeshComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.f));
	StaticMeshComp->SetWorldScale3D(FVector(0.5f));
	
	PrimaryActorTick.bCanEverTick = true;

	StartLocation = FVector(-330.f, 2800.f, 50.f);
}

void ACrazyElevator::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(StartLocation);

}

void ACrazyElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// ���� �ٲ�� �͵� �ð����� �ϸ� �ȵǰ� �̵� �Ÿ��� �������� �ؾ߰���
	// �ð����� �ϸ� �ӵ��� �ٲ��� �� �̵��ϴ� �Ÿ��� �޶���
	if (Distance >= 400.0f || Distance < 0.0f)
	{
		SpeedZ *= -1;
	}

	FVector MoveZAxis(0.f, 0.f, SpeedZ * DeltaTime);
	FRotator YawRotation(0.f, RotationSpeed * DeltaTime, 0.f);

	float AngleDegrees = GetGameTimeSinceCreation() * 90.0f;
	float AngleRadians = FMath::DegreesToRadians(AngleDegrees);
	//float Pi = FMath::DegreesToRadians(-90.0f);
	FVector NewScale(0.35*FMath::Sin(AngleRadians) + 0.6f);

	FTransform NewTransform(YawRotation, MoveZAxis, NewScale);

	AddActorLocalTransform(NewTransform);

	Distance += SpeedZ * DeltaTime;
}

void ACrazyElevator::ResetActorPosition()
{
	SetActorLocation(FVector::ZeroVector);
}

float ACrazyElevator::GetRotationSpeed() const
{
	return RotationSpeed;
}

