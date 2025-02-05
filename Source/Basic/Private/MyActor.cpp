#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
	// ��Ʈ ������Ʈ ����
	//SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	//SetRootComponent(SceneRoot);

	// ĸ�� �ݸ��� ������Ʈ�� ��Ʈ ������Ʈ�� ����
	CapsuleRoot = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleRoot"));
	SetRootComponent(CapsuleRoot);

	// ��Ʈ ������Ʈ�� �� �״�� ��Ʈ�̱� ������ ������� ��ġ ����� �Ұ���
	//CapsuleRoot->SetRelativeLocation(FVector(0, 0, 80));
	// ���忡 ���� ��ġ�� ���� ����
	CapsuleRoot->SetWorldLocation(FVector(0, 0, 90));
	// x�� �״��, y�� ���� ���̰�, z�� �ø��� ������
	// ĸ�� ������Ʈ�� x,y���� ���������� �����ϴ� ���� �������� ����
	// �������� �ݳ��̸� ���� ����
	CapsuleRoot->SetCapsuleSize(20.f, 90.f);

	// ���̷�Ż �޽� �߰�
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(CapsuleRoot);

	// ��Ʈ ������Ʈ�� ���� ������� ��ġ ����
	SkeletalMeshComp->SetRelativeLocation(FVector(0, 0, -90));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SMeshAsset(TEXT("/Game/Resources/Characters/Meshes/SKM_Manny.SKM_Manny"));
	if (SMeshAsset.Succeeded())
	{
		SkeletalMeshComp->SetSkeletalMesh(SMeshAsset.Object);
	}

	// ���̷�Ż �޽ÿ� ��Ƽ���� ����
	static ConstructorHelpers::FObjectFinder<UMaterial> GoldMaterialAsset(TEXT("/Game/Resources/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (GoldMaterialAsset.Succeeded())
	{
		SkeletalMeshComp->SetMaterial(0, GoldMaterialAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> RustMaterialAsset(TEXT("/Game/Resources/Materials/M_Metal_Rust.M_Metal_Rust"));
	if (RustMaterialAsset.Succeeded())
	{
		SkeletalMeshComp->SetMaterial(1, RustMaterialAsset.Object);
	}

	// ����� ������Ʈ �߰�
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	AudioComp->SetupAttachment(SkeletalMeshComp);

	// ����� ������Ʈ�� ������ ���� ���ҽ� ����(USoundCue�� ��� USoundBase ���)
	//static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Resources/Audio/Fire01_Cue.Fire01_Cue"));
	//if (SoundAsset.Succeeded())
	//{
	//	AudioComp->SetSound(SoundAsset.Object);
	//}

	// ������ �� ������Ʈ �߰�
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(SkeletalMeshComp);
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 150));
	// FRotator�� pitch(�� �����Ÿ���), yaw(���������ϱ�), roll(����̱�) ������ ����
	SpringArmComp->SetRelativeRotation(FRotator(-20.f, 90.f, 0.f));
	SpringArmComp->TargetArmLength = 200;
	SpringArmComp->bUsePawnControlRotation = true;

	// ī�޶� ������Ʈ �߰�
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
}
