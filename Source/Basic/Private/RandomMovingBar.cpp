// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomMovingBar.h"

ARandomMovingBar::ARandomMovingBar()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(SceneRoot);
	StaticMeshComp->SetupAttachment(SceneRoot);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_PillarFrame.SM_PillarFrame"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	StaticMeshComp->SetRelativeRotation(FRotator(90.f, 0.0f, 0.0f));
	StaticMeshComp->SetRelativeScale3D(FVector(1.0f, 1.0f, 5.0f));
	StaticMeshComp->SetRelativeLocation(FVector(1000.0f, 0.0f, 0.0f));

	SpeedY = 200.0f;
	SpeedZ = 200.0f;

	StartLocationY = 1400.0f;
	EndLocationY = 2600.0f;
	StartLocationZ = 720.0f;
	EndLocationZ = 1000.0f;
	
	MinOfRange = 100.0f;
	MaxOfRange = 280.0f;
}

void ARandomMovingBar::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(FVector(0.0f, StartLocationY, StartLocationZ));

	EndLocationZ = FMath::FRandRange(StartLocationZ + MinOfRange, StartLocationZ + MaxOfRange);
	TargetLocationY = EndLocationY;
	TargetLocationZ = EndLocationZ;
}

void ARandomMovingBar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MinOfRange > MaxOfRange || MinOfRange < 0.0f)
	{
		MinOfRange = 100.0f;
	}
	if (MaxOfRange < MinOfRange)
	{
		MaxOfRange = 280.0f;
	}

	AddActorLocalOffset(FVector(0.0f, SpeedY * DeltaTime, SpeedZ * DeltaTime));
	//UE_LOG(LogTemp, Warning, TEXT("Z : %f"), GetActorLocation().Z);
	//UE_LOG(LogTemp, Warning, TEXT("TargetLocationZ : %f"), TargetLocationZ);

	if (GetActorLocation().Y > EndLocationY || GetActorLocation().Y < StartLocationY)
	{
		FVector CurrentLocation = GetActorLocation();
		// ��ġ ����
		FVector CorrectLocation(CurrentLocation.X, TargetLocationY, CurrentLocation.Z);
		SetActorLocation(CorrectLocation);

		TargetLocationY = (CorrectLocation.Y == StartLocationY) ? EndLocationY : StartLocationY;
		SpeedY *= -1;
	}

	if (GetActorLocation().Z > EndLocationZ || GetActorLocation().Z < StartLocationZ)
	{
		FVector CurrentLocation = GetActorLocation();
		// ��ġ ����
		FVector CorrectLocation(CurrentLocation.X, CurrentLocation.Y, TargetLocationZ);
		SetActorLocation(CorrectLocation);

		// ��ǥ ������ EndLocation�̸� if���� �������� �� ���ο� EndLocationZ�� �������� �����ϴµ�
		// �� ���� ���� ��ġ Z���� ���� ���� �ɸ���, ���� ����Ŭ���� ���� if���� �ɷ��� Z���� StartLocationZ�� ������ �Ǿ �̻��ϰ� �۵���
		//if (TargetLocationZ == EndLocationZ)
		 
		// ���� ��ġ Z�� StartLocationZ�� ��(�ؿ� ���� ��) ���ο� EndLocationZ�� ����
		if(TargetLocationZ == StartLocationZ)
		{
			EndLocationZ = FMath::FRandRange(StartLocationZ + MinOfRange, StartLocationZ + MaxOfRange);
		}

		TargetLocationZ = (CorrectLocation.Z == StartLocationZ) ? EndLocationZ : StartLocationZ;
		SpeedZ *= -1;
	}
}

