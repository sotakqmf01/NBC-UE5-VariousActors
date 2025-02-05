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
	
	// �̷��� Tick()�� �ƴ� BeginPlay()���� Ÿ�̸Ӹ� �����س����� Tick()�� ������� �ʾƵ��Ǿ ������ ������ �� �ִµ�
	// ��� ������ �����Ϳ��� �������� �ٲ� ���� ����(�ٲ� ���� �ִ��� ������ �� ���� ����)
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
		// nullptr�� ������ ���� SpawnActor���� Potion�� ������ �� ����
		SpawnedPotion = nullptr;
	}
}

void APotionSpawner::SpawnActor()
{
	//FDateTime Now = FDateTime::UtcNow();
	//FString TimeString = Now.ToString(TEXT("%H:%M:%S.%f"));
	//UE_LOG(LogTemp, Warning, TEXT("Current time with milliseconds: %s"), *TimeString);

	// LifeSpan() Ȱ���ϴ� ��
	//if (!IsValid(SpawnedPotion))
	//	SpawnedPotion = nullptr;

	if (SpawnedPotion == nullptr)
	{
		FVector SpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, 153.0f);
		FRotator SpawnRotation = GetActorRotation();

		SpawnedPotion = GetWorld()->SpawnActor<ASpawnedPotion>(SpawnLocation, SpawnRotation);
	}
}

// ���� ���� ���� => ���� ���̺� �˾ƺ���