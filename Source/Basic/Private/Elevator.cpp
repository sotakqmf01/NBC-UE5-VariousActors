// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

AElevator::AElevator()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(SceneRoot);
	StaticMeshComp->SetupAttachment(SceneRoot);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_AssetPlatform.SM_AssetPlatform"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	StaticMeshComp->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.0f));

	SpeedZ = 200.0f;
	//InterSpeedZ = 0.4f;
	StartLocation = FVector(0.0f, 1000.0f, 0.0f);
	EndLocation = FVector(0.0f, 1000.0f, 700.0f);
	
	bIsPaused = false;
}

void AElevator::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(StartLocation);

	// ���� ��ġ�� Ÿ���� �����ڿ��� �ʱ�ȭ�ϸ� �����Ϳ��� �ν��Ͻ��� ���� �ٲٴ��� �ٲ� ���� ������ �ȵ�
	// BeginPlay()���� �ʱ�ȭ�ؾ� �����Ϳ��� ������ ������ �ʱ�ȭ�Ǿ ����� �۵�
	CurrentLocation = StartLocation;
	CurrentTarget = EndLocation;
}

void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsPaused)
	{
		return;
	}

	CurrentLocation = GetActorLocation();

	// VInterpTo():���� ����
	// ���� ������ ����ϸ� ��ǥ������ ���� �ٿͰ��� �ӵ��� �ʹ� �������� ��Ȯ�� ��ǥ������ �����ϱ���� �ʹ��ʹ� �����ɸ�
	// �ؿ� ���� ��ġ�� ��ǥ ��ġ ������ �Ÿ��� IsNearlyZero()���� 1.0f�� 2.0f ���� ������ ���ϴ� �ɷ� �ٲٸ� �Ǳ� ��
	//FVector NewLocation = FMath::VInterpTo(CurrentLocation, CurrentTarget, DeltaTime, InterSpeedZ);
	
	// VInterConstantTo():���� �ӵ� ����
	// MovingPlatform���� ��ġ�� �׳� �ӵ�*DeltaTime�� ������ ��ó�� �۵�
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, CurrentTarget, DeltaTime, SpeedZ);
	
	SetActorLocation(NewLocation);

	
	//if(FVector::Dist(CurrentLocation, CurrentTarget) < 2.0f)
	if (FMath::IsNearlyZero(FVector::Dist(CurrentLocation, CurrentTarget)))
	{
		CurrentLocation = CurrentTarget;
		SetActorLocation(CurrentTarget);
		bIsPaused = true;

		FTimerHandle PauseTimerHandle;

		GetWorldTimerManager().SetTimer(PauseTimerHandle, this, &AElevator::ResumeMovement, 2.0f, false);
	}
}

void AElevator::ResumeMovement()
{
	bIsPaused = false;
	CurrentTarget = (CurrentLocation == StartLocation) ? EndLocation : StartLocation;
}

