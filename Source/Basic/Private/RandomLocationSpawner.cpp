// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomLocationSpawner.h"
#include "Components/BoxComponent.h"
#include "Item.h"


ARandomLocationSpawner::ARandomLocationSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));

	SetRootComponent(SceneRoot);
	SpawnVolume->SetupAttachment(SceneRoot);

	XAxisMin = -1000;
	XAxisMax = 1000;
	YAxisMin = 3133;
	YAxisMax = 4633;
	ZAxis = 1240;
}

void ARandomLocationSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle SpawnTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ARandomLocationSpawner::SpawnActor, 1.0f, true, 1.0f);
}

void ARandomLocationSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("ItemSet's Element Count : %d"), ItemSet.Num());
	//if (ItemSet.Num() < 10)
	//{
	//	SpawnActor();
	//}
}

void ARandomLocationSpawner::SpawnActor()
{
	bool bIsPossibleLocation = false;
	FVector SpawnLocation;
	FRotator SpawnRotation;

	OrganizeSet();

	// ��ǻ�Ͱ� ������ ��ǥ�� �̴� Ƚ���� �ִ� 10��
	int32 LoopCount = 10;

	while (!bIsPossibleLocation && LoopCount > 0)
	{
		float RandomX = FMath::FRandRange(XAxisMin, XAxisMax);
		float RandomY = FMath::FRandRange(YAxisMin, YAxisMax);
		SpawnLocation = FVector(RandomX, RandomY, ZAxis);
		SpawnRotation = FRotator(GetActorRotation());

		for (AItem* item : ItemSet)
		{
			if (FVector::Dist(item->GetActorLocation(), SpawnLocation) < 100.0f)
			{	
				// ���͸� �������� �� �������� ���
				bIsPossibleLocation = false;
				break;
			}
			else
			{
				bIsPossibleLocation = true;
			}
		}

		if (ItemSet.Num() == 0)
		{
			bIsPossibleLocation = true;
		}

		--LoopCount;
	}

	// ������ �� �ִ� ���� ��ǥ�� �̾��� ��
	if (bIsPossibleLocation)
	{
		// �ִ� 10�� ���� �����Ǿ� ���� �� ���� 
		if (ItemSet.Num() < 10)
		{
			AItem* NewItem = GetWorld()->SpawnActor<AItem>(SpawnLocation, SpawnRotation);
			ItemSet.Add(NewItem);
		}
	}
}

void ARandomLocationSpawner::OrganizeSet()
{
	TArray<AItem*> ItemToRemove;

	for (AItem* item : ItemSet)
	{
		if (!IsValid(item))
		{
			ItemToRemove.Add(item);
		}
	}

	for (AItem* item : ItemToRemove)
	{
		ItemSet.Remove(item);
	}
}
