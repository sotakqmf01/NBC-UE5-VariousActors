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
	//SetActorRotation(ItemRotation);		// pitch(y)-yaw(z)-roll(z) ����
	//SetActorScale3D(FVector(2.0f));

	//FVector NewLocation(300.f, 300.f, 300.f);
	//FRotator NewRotation(0.f, 0.f, 45.f);
	//FVector NewScale(2.f);

	//FTransform NewTransform(NewRotation, NewLocation, NewScale);	// ȸ��, ��ġ, ũ�� ����
	//SetActorTransform(NewTransform);

	SetLifeSpan(5.0f);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		// LocalRotation()�� WorldRotation() ���̴� ������ ����� �������� ������ ���ΰ��� ����
		// �������Ʈ�� �� ������Ʈ�� ��ġ�ϰ� ctrl + `�� ����� �ٲٸ鼭 �ű�� ȸ���ϰ� �׷��µ� �װ� �����ϸ� ��
		// LocalRotation()�� Local �����, WorldRotation()�� World ����� �������� ȸ��
		//AddActorLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
		AddActorWorldRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));

		// SetActorRotation()�� ����ؼ� ȸ�� ��ų �� ���� ������?
		// �Ǳ� �Ǵµ� �̷��� ���� �ͺ��� �׳� ������� �ִ°� ���°� �� �ٸ� ����Ǵϱ� ���ҵ�
		//FRotator CurrentRotation = GetActorRotation() + FRotator(0.f, RotationSpeed * DeltaTime, 0.f);
		//SetActorRotation(CurrentRotation);
	}
	
}