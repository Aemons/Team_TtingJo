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
	//Damage�� ������ �� Damage.Power�� 0���� �ʱ�ȭ
	Damage.Power = 0;
	
	//DamageEvent�� HitData�� ��ȿ�Ҷ�
	if (!!Damage.Event && !!Damage.Event->HitData)
	{
		FHitData* data = Damage.Event->HitData;

		data->PlayMontage(this);
		data->PlayHitStop(GetWorld());
		data->PlaySoundWave(this);
		data->PlayEffect(GetWorld(), GetActorLocation(), GetActorRotation());
		
		LaunchToEnemy();
	}

	//HP�� 0 ���� �۰ų� ������
	if (StatusComp->IsDead())
	{
		//StateType�� DeadMode�� �ٲ�
		StateComp->SetDeadMode();
		return;
	}

	//Damageó���� �������� ���� ���� DamageData�� ���� �ʱ�ȭ ��Ŵ
	Damage.Character = nullptr;
	Damage.Causer = nullptr;
	Damage.Event = nullptr;
}

void AJHS_Enemy::Dead()
{
	//�׾��¶� �� �浹�ϸ� �ȵǹǷ� Collision Off
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (!!DeadMontage)
		PlayAnimMontage(DeadMontage, DeadPlayRate);

	//TODO : Enemy Dead �� ����Ȯ���� �ܻ��� ����
	//������ ���� ���ϰ� ������ ������ Ȯ���� ������
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
		//���� �� ��ġ
		FVector Start = GetActorLocation();
		//���� Target�� �ִ� ��ġ
		FVector Target = Damage.Character->GetActorLocation();
		//���� Target ������ �Ÿ�, ����
		FVector Direction = Target - Start;
		//����ȭ�� ���� ���⸸ ����
		Direction.Normalize();

		//Enemy���忡�� ����� �ؾ� �ϹǷ� �չ������� �����°� �ƴ� �ڹ������� ������ ��
		LaunchCharacter((-Direction * data->Launch), false, false);
		//���ư� �Ŀ� Enemy�� Target�� �ٶ󺸰� ��
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Start, Target));
	}

}

void AJHS_Enemy::CreateDeathPose()
{
	//AActor�� �״� ������ ������ ������ ��ü�� ����
	AActor* DeathImage = GetWorld()->SpawnActor<AActor>(GetActorLocation(), GetActorRotation());
	CheckNull(DeathImage);

	//SkeletalMesh ���� �� �Ҵ�
	UPoseableMeshComponent* PoseMesh = NewObject<UPoseableMeshComponent>(DeathImage);
	CheckNull(PoseMesh)

	//PoseMesh Setting
	//PoseableMehsComponent�� �⺻������ �浹ü�� ������ �ʴ´�
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

	//PoseMesh���� �浹ü�� �� �Ҵ��ϰ� �����ϴ� ���
	//���� Mesh�� ���ܳ��� ������� �ʰ� ����� ��� �浹�ϰ� �����
	GetMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);

	//DeathPose�� �ڿ������� ���̱� ���ؼ� ���� Mesh�� ������� ������ ����ó��
	GetMesh()->SetVisibility(false);

	//PoseMesh�� Material�� ����ȭ ó���� Material�� �ٲ� (�ܻ� ó�� ���̰�)
	//������ material�� �������� �������� �ʴ� ������ materald�� �����ϰ� �����Ǿ� �ְ�
	//����ȭ ó���� �ҷ��� ���Ľ�Ƽ�� Ȱ��ȭ ���Ѿ� �ϴµ� �׷��� ������ material��
	//�޶����� ������ ���� material�� �����ϴ� �ͺ��� ������ ó���� ���� material��
	//��ü�ϴ� ������� ����
	UMaterialInterface* MatDynamic = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Script/Engine.Material'/Game/Characters/Mannequins/Materials/M_Mannequin_Test.M_Mannequin_Test'")));
	if (MatDynamic)
	{
		//material ������ 1���� �ƴ� ������ Mesh�� ������ �����Ƿ� �ݺ��� ����
		for (int32 i = 0; i < PoseComp->GetNumMaterials(); i++)
		{
			//�� material ���Կ� ���� material�� ����
			PoseComp->SetMaterial(i, MatDynamic);
		}
	}

	//PoseMesh�� NewObject�� ���������ϱ� Destroy�ҋ� nullptr ����� ��
	//�ش� ������ Player���� ��ȣ�� ������ �۵��ϴ� �������� ���濹��
	//PoseMesh->DestroyComponent();
	//PoseMesh = nullptr;
}


void AJHS_Enemy::End_Hitted()
{
	//Hitted ���°� �������� �ٽ� Idle ���·� �ٽ� ������
	StateComp->SetIdleMode();
}

void AJHS_Enemy::End_Dead()
{
	if (bIsChance == true)
	{
		//Echo ����� �߰� ���� ����
	}
	else
	{
		GetMesh()->bPauseAnims = true;
		//SetLifeSpan(3.0f);
	}
}
