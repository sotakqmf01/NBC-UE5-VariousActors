#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
	// 루트 컴포넌트 지정
	//SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	//SetRootComponent(SceneRoot);

	// 캡슐 콜리전 컴포넌트를 루트 컴포넌트로 지정
	CapsuleRoot = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleRoot"));
	SetRootComponent(CapsuleRoot);

	// 루트 컴포넌트는 말 그대로 루트이기 때문에 상대적인 위치 계산이 불가능
	//CapsuleRoot->SetRelativeLocation(FVector(0, 0, 80));
	// 월드에 대한 위치는 조정 가능
	CapsuleRoot->SetWorldLocation(FVector(0, 0, 90));
	// x축 그대로, y축 조금 줄이고, z축 늘리고 싶은데
	// 캡슐 컴포넌트는 x,y축을 독립적으로 조정하는 것을 지원하지 않음
	// 반지름과 반높이만 설정 가능
	CapsuleRoot->SetCapsuleSize(20.f, 90.f);

	// 스켈레탈 메시 추가
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(CapsuleRoot);

	// 루트 컴포넌트에 대해 상대적인 위치 변경
	SkeletalMeshComp->SetRelativeLocation(FVector(0, 0, -90));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SMeshAsset(TEXT("/Game/Resources/Characters/Meshes/SKM_Manny.SKM_Manny"));
	if (SMeshAsset.Succeeded())
	{
		SkeletalMeshComp->SetSkeletalMesh(SMeshAsset.Object);
	}

	// 스켈레탈 메시에 머티리얼 적용
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

	// 오디오 컴포넌트 추가
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	AudioComp->SetupAttachment(SkeletalMeshComp);

	// 오디오 컴포넌트에 지정될 사운드 리소스 적용(USoundCue가 없어서 USoundBase 사용)
	//static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Resources/Audio/Fire01_Cue.Fire01_Cue"));
	//if (SoundAsset.Succeeded())
	//{
	//	AudioComp->SetSound(SoundAsset.Object);
	//}

	// 스프링 암 컴포넌트 추가
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(SkeletalMeshComp);
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 150));
	// FRotator는 pitch(고개 끄덕거리기), yaw(도리도리하기), roll(기울이기) 순으로 저장
	SpringArmComp->SetRelativeRotation(FRotator(-20.f, 90.f, 0.f));
	SpringArmComp->TargetArmLength = 200;
	SpringArmComp->bUsePawnControlRotation = true;

	// 카메라 컴포넌트 추가
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
}
