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

	// 현재 위치와 타겟을 생성자에서 초기화하면 에디터에서 인스턴스의 값을 바꾸더라도 바꾼 값이 적용이 안됨
	// BeginPlay()에서 초기화해야 에디터에서 변경한 값으로 초기화되어서 제대로 작동
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

	// VInterpTo():감속 보간
	// 감속 보간을 사용하면 목표지점에 거의 다와가면 속도가 너무 느려져서 정확히 목표지점에 도달하기까지 너무너무 오래걸림
	// 밑에 현재 위치와 목표 위치 사이의 거리를 IsNearlyZero()말고 1.0f나 2.0f 보다 작은지 비교하는 걸로 바꾸면 되긴 됨
	//FVector NewLocation = FMath::VInterpTo(CurrentLocation, CurrentTarget, DeltaTime, InterSpeedZ);

	// VInterConstantTo():일정 속도 보간
	// MovingPlatform에서 위치에 그냥 속도*DeltaTime을 더해준 것처럼 작동
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