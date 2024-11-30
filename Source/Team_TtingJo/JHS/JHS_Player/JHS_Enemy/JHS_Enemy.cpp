#include "JHS_Enemy.h"
#include "JHS_Global.h"

#include "Engine/CollisionProfile.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PoseableMeshComponent.h"

#include "Kismet/KismetMathLibrary.h"

#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"

#include "JHS_Component/JHS_StateComponent.h"
#include "JHS_Component/JHS_MovemetComponent.h"
#include "JHS_Component/JHS_WeaponComponent.h"
#include "JHS_Component/JHS_StatusComponent.h"

#include "JHS_Weapon/JHS_WeaponStructures.h"

AJHS_Enemy::AJHS_Enemy()
{
	PrimaryActorTick.bCanEverTick = false;

	//Create Component
	MovementComp = CreateDefaultSubobject<UJHS_MovemetComponent>(TEXT("MovementComp"));
	StateComp = CreateDefaultSubobject<UJHS_StateComponent>(TEXT("StateComp"));
	StatusComp = CreateDefaultSubobject<UJHS_StatusComponent>(TEXT("StatusComp"));
	PoseComp = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseComp"));
	////////////////////////////////////////////////////////////////

	//AttachComponent
	PoseComp->SetupAttachment(GetMesh());

	//Default Setting
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	////////////////////////////////////////////////////////////////
}

void AJHS_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
	StateComp->OnStateTypeChanged.AddDynamic(this, &AJHS_Enemy::OnStateTypeChanged);
}

void AJHS_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJHS_Enemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	//case EStateType::Idle:
		//break;
	//case EStateType::Equip:
		//break;
	case EStateType::Hitted:
		Hitted();
		break;
	case EStateType::Dead:
		Dead();
		break;
	//case EStateType::MainAction:
		//break;
	case EStateType::Max:
		break;
	default:
		break;
	}
}

float AJHS_Enemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Damage.Power = damage;
	Damage.Character = Cast<ACharacter>(EventInstigator->GetPawn());
	Damage.Causer = DamageCauser;
	Damage.Event = (FMainActionDamageEvent*)&DamageEvent;
	
	StateComp->SetHittedMode();
	
	return damage;
}

void AJHS_Enemy::Hitted()
{
	StatusComp->Damage(Damage.Power);
	//Damage를 전달한 후 Damage.Power를 0으로 초기화
	Damage.Power = 0;
	
	//DamageEvent와 HitData가 유효할때
	if (!!Damage.Event && !!Damage.Event->HitData)
	{
		FHitData* data = Damage.Event->HitData;

		data->PlayMontage(this);
		data->PlayHitStop(GetWorld());
		data->PlaySoundWave(this);
		data->PlayEffect(GetWorld(), GetActorLocation(), GetActorRotation());
		
		LaunchToEnemy();
	}

	//HP가 0 보다 작거나 같을때
	if (StatusComp->IsDead())
	{
		//StateType을 DeadMode로 바꿈
		StateComp->SetDeadMode();
		return;
	}

	//Damage처리가 끝났으면 이후 들어올 DamageData를 위해 초기화 시킴
	Damage.Character = nullptr;
	Damage.Causer = nullptr;
	Damage.Event = nullptr;
}

void AJHS_Enemy::Dead()
{
	//죽었는때 또 충돌하면 안되므로 Collision Off
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (!!DeadMontage)
		PlayAnimMontage(DeadMontage, DeadPlayRate);

	//TODO : Enemy Dead 후 일정확률로 잔상이 남음
	//랜덤한 수를 구하고 임의의 일정한 확률을 설정함
	const float Chance = FMath::RandRange(DeadPoseChance.X, DeadPoseChance.Y);
	if (Chance >= 0.5f)
	{
		bIsChance = true;
		CreateDeathPose();
	}
}

void AJHS_Enemy::LaunchToEnemy()
{
	FHitData* data = Damage.Event->HitData;

	if (StatusComp->IsDead() == false)
	{
		//현재 내 위치
		FVector Start = GetActorLocation();
		//현재 Target이 있는 위치
		FVector Target = Damage.Character->GetActorLocation();
		//나와 Target 사이의 거리, 방향
		FVector Direction = Target - Start;
		//정규화를 통해 방향만 남김
		Direction.Normalize();

		//Enemy입장에서 계산을 해야 하므로 앞방향으로 날리는게 아닌 뒤방향으로 날려야 함
		LaunchCharacter((-Direction * data->Launch), false, false);
		//날아간 후에 Enemy가 Target을 바라보게 함
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Start, Target));
	}

}

void AJHS_Enemy::CreateDeathPose()
{
	//AActor로 죽는 순간의 동작을 저장할 객체를 만듬
	AActor* DeathImage = GetWorld()->SpawnActor<AActor>(GetActorLocation(), GetActorRotation());
	CheckNull(DeathImage);

	//SkeletalMesh 생성 및 할당
	UPoseableMeshComponent* PoseMesh = NewObject<UPoseableMeshComponent>(DeathImage);
	CheckNull(PoseMesh)

	//PoseMesh Setting
	//PoseableMehsComponent는 기본적으로 충돌체를 가지지 않는다
	////////////////////////////////////////////////////////////////////////////
	PoseComp->RegisterComponent();
	PoseComp->AttachToComponent(DeathImage->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
	PoseComp->SetSkeletalMesh(GetMesh()->SkeletalMesh);
	PoseComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PoseComp->SetWorldLocation(this->GetActorLocation() + FVector(0, 0, -90));
	PoseComp->SetWorldRotation(this->GetActorRotation() + FRotator(0, -90, 0));
	////////////////////////////////////////////////////////////////////////////
	
	//Pose Copy
	PoseComp->CopyPoseFromSkeletalComponent(GetMesh());

	//PoseMesh에서 충돌체를 또 할당하고 설정하는 대신
	//기준 Mesh를 숨겨놓고 사라지지 않게 만들고 대신 충돌하게 만든다
	GetMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);

	//DeathPose가 자연스럽게 보이기 위해서 기준 Mesh가 사라지기 전까지 숨김처리
	GetMesh()->SetVisibility(false);

	//PoseMesh의 Material을 투명화 처리한 Material로 바꿈 (잔상 처럼 보이게)
	//기존의 material을 동적으로 수정하지 않는 이유는 materald이 복잡하게 설정되어 있고
	//투명화 처리를 할려면 오파시티를 활성화 시켜야 하는데 그러면 기존의 material이
	//달라지기 때문의 기존 material을 수정하는 것보다 별도의 처리를 해준 material로
	//교체하는 방식으로 구현
	UMaterialInterface* MatDynamic = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Script/Engine.Material'/Game/Characters/Mannequins/Materials/M_Mannequin_Test.M_Mannequin_Test'")));
	if (MatDynamic)
	{
		//material 슬롯이 1개가 아닌 복수인 Mesh가 있을수 있으므로 반복문 돌림
		for (int32 i = 0; i < PoseComp->GetNumMaterials(); i++)
		{
			//각 material 슬롯에 투명 material을 설정
			PoseComp->SetMaterial(i, MatDynamic);
		}
	}

	//PoseMesh는 NewObject로 생성했으니까 Destroy할떄 nullptr 해줘야 함
	//해당 구문은 Player에서 신호가 들어오면 작동하는 구문으로 변경예정
	//PoseMesh->DestroyComponent();
	//PoseMesh = nullptr;
}


void AJHS_Enemy::End_Hitted()
{
	//Hitted 상태가 끝났으면 다시 Idle 상태로 다시 돌려줌
	StateComp->SetIdleMode();
}

void AJHS_Enemy::End_Dead()
{
	if (bIsChance == true)
	{
		//Echo 출력후 추가 적인 설정
	}
	else
	{
		GetMesh()->bPauseAnims = true;
		//SetLifeSpan(3.0f);
	}
}
