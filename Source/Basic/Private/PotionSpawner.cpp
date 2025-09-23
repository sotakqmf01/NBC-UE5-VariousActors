// Fill out your copyright notice in the Description page of Project Settings.

#include "PotionSpawner.h"
#include "SpawnedPotion.h"

// Sets default values
APotionSpawner::APotionSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(SceneRoot);
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Lamp_Ceiling.SM_Lamp_Ceiling"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	StaticMeshComp->SetRelativeRotation(FRotator(180.0f, 0.0f, 0.0f));

	SpawnedPotion = nullptr;

	//PotionLifeTime = 8.0f;
	//PotionDeleteDelay = 5.0f;
}

void APotionSpawner::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle SpawnTimerHandle;
	FTimerHandle DespawnTimerHandle;

	// 이렇게 Tick()이 아닌 BeginPlay()에서 타이머를 설정해놓으면 Tick()을 사용하지 않아도되어서 성능이 좋아질 수 있는데
	// 대신 값들을 에디터에서 동적으로 바꿀 수는 없음(바꿀 수는 있더라도 적용을 할 수가 없음)
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APotionSpawner::SpawnActor, 10.0f, true, 0.0f);
	GetWorld()->GetTimerManager().SetTimer(DespawnTimerHandle, this, &APotionSpawner::DespawnActor, 10.0f, true, 7.0f);
}

void APotionSpawner::DespawnActor()
{
	//FDateTime Now = FDateTime::UtcNow();
	//FString TimeString = Now.ToString(TEXT("%H:%M:%S.%f"));
	//UE_LOG(LogTemp, Warning, TEXT("Current time with milliseconds: %s"), *TimeString);

	if (SpawnedPotion != nullptr)
	{
		SpawnedPotion->Destroy();
		// nullptr로 만들어야 다음 SpawnActor에서 Potion을 생성할 수 있음
		SpawnedPotion = nullptr;
	}
}

void APotionSpawner::SpawnActor()
{
	//FDateTime Now = FDateTime::UtcNow();
	//FString TimeString = Now.ToString(TEXT("%H:%M:%S.%f"));
	//UE_LOG(LogTemp, Warning, TEXT("Current time with milliseconds: %s"), *TimeString);

	// LifeSpan() 활용하는 법
	//if (!IsValid(SpawnedPotion))
	//	SpawnedPotion = nullptr;

	if (SpawnedPotion == nullptr)
	{
		FVector SpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, 153.0f);
		FRotator SpawnRotation = GetActorRotation();

		SpawnedPotion = GetWorld()->SpawnActor<ASpawnedPotion>(SpawnLocation, SpawnRotation);
	}
}

// 랜덤 액터 스폰 => 에셋 테이블 알아보기