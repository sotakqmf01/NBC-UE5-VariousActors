// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

DEFINE_LOG_CATEGORY(LogUnreal);

// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Star_B.SM_Star_B"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Debuff_A.M_Debuff_A"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	//ItemLocation = FVector(0.f, 10.f, 85.f);
	//ItemRotation = FRotator(0.f, 0.f, 45.f);
	RotationSpeed = 90.f;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	//SetActorLocation(ItemLocation);
	//SetActorRotation(ItemRotation);		// pitch(y)-yaw(z)-roll(z) 순서
	//SetActorScale3D(FVector(2.0f));

	//FVector NewLocation(300.f, 300.f, 300.f);
	//FRotator NewRotation(0.f, 0.f, 45.f);
	//FVector NewScale(2.f);

	//FTransform NewTransform(NewRotation, NewLocation, NewScale);	// 회전, 위치, 크기 순서
	//SetActorTransform(NewTransform);

	SetLifeSpan(5.0f);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		// LocalRotation()과 WorldRotation() 차이는 누구의 기즈모를 기준으로 동작할 것인가의 차이
		// 블루프린트할 때 오브젝트들 배치하고 ctrl + `로 기즈모 바꾸면서 옮기고 회전하고 그랬는데 그걸 생각하면 됨
		// LocalRotation()은 Local 기즈모, WorldRotation()은 World 기즈모를 기준으로 회전
		//AddActorLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
		AddActorWorldRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));

		// SetActorRotation()을 사용해서 회전 시킬 수 있지 않을까?
		// 되긴 되는데 이렇게 쓰는 것보다 그냥 만들어져 있는거 쓰는게 한 줄만 쓰면되니까 편할듯
		//FRotator CurrentRotation = GetActorRotation() + FRotator(0.f, RotationSpeed * DeltaTime, 0.f);
		//SetActorRotation(CurrentRotation);
	}
	
}