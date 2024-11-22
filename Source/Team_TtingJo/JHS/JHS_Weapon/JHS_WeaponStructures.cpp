#include "JHS_WeaponStructures.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

#include "Animation/AnimMontage.h"
#include "Kismet/GameplayStatics.h"

#include "FXSystem.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "JHS_Component/JHS_StateComponent.h"
#include "JHS_Component/JHS_MovemetComponent.h"


//MainAction Struct Data
void FMainActionData::MainAction(ACharacter* InOwner)
{
	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRate);
}
///////////////////////////////////////////////////////////////


//HitData Struct Data Function
void FHitData::SendDamage(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther)
{
	FMainActionDamageEvent DamageEvent;
	DamageEvent.HitData = this;

	//실제로 Damage를 주는 부분
	InOther->TakeDamage(Damage, DamageEvent, InAttacker->GetController(), InAttackCuaser);
}

void FHitData::PlayMontage(ACharacter* InOwner)
{
	UJHS_MovemetComponent* MovementComp = Cast<UJHS_MovemetComponent>(InOwner->GetComponentByClass(UJHS_MovemetComponent::StaticClass()));

	if (!!MovementComp)
		InOwner->PlayAnimMontage(Montage, PlayRate);
}

void FHitData::PlayHitStop(UWorld* InWorld)
{
	//해당 히트스탑 함수는 추후가 꼭 다시 공부하고 필히 정리해 놓을 것

	//StopTime Check
	CheckTrue(FMath::IsNearlyZero(HitStopTime));

	//현재 레벨에서 움직이는 Object들을 찾음
	TArray<APawn*> Pawns;
	for (AActor* Actor : InWorld->GetCurrentLevel()->Actors)
	{
		//현재 레벨에서 찾은 Pawn을 ACharacter형태로 캐스팅
		APawn* Pawn = Cast<ACharacter>(Actor);

		if (!!Pawn)
		{
			//지수표기법 : 그냥 한번 써봄
			//1 * 10^(-3), 0.001
			Pawn->CustomTimeDilation = 1e-3f;
			Pawns.Add(Pawn);
		}
	}

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([=]()
	{
		for (APawn* pawn : Pawns)
			pawn->CustomTimeDilation = 1.0f;
	});

	FTimerHandle Handle;
	InWorld->GetTimerManager().SetTimer(Handle, TimerDelegate, HitStopTime, false);
}

void FHitData::PlaySoundWave(ACharacter* InOwner)
{
	CheckNull(Sound);

	UWorld* World = InOwner->GetWorld();
	FVector Location = InOwner->GetActorLocation();

	UGameplayStatics::SpawnSoundAtLocation(World, Sound, Location);
}

void FHitData::PlayEffect(UWorld* InWorld, const FVector& InLocation, const FRotator& InRotation)
{
	CheckNull(Effect);

	UFXSystemAsset* FXAsset = Effect;
	USkeletalMeshComponent* Mesh = nullptr;
	
	UParticleSystem* Particle = Cast<UParticleSystem>(FXAsset);
	UNiagaraSystem* Niagara = Cast<UNiagaraSystem>(FXAsset);

	FName SocketName = "";

	FTransform Transform;
	Transform.SetLocation(InLocation + InRotation.RotateVector(EffectLocation));
	Transform.SetScale3D(EffectScale);

	FVector location = Transform.GetLocation();
	FRotator rotation = FRotator(Transform.GetRotation());
	FVector scale = Transform.GetScale3D();

	//Effect Attached
	if (!!Mesh)
	{
		if (!!Particle)
		{
			UGameplayStatics::SpawnEmitterAttached(Particle, Mesh, SocketName, location, rotation, scale);
			
			return;
		}

		if (!!Niagara)
		{
			UNiagaraFunctionLibrary::SpawnSystemAttached(Niagara, Mesh, SocketName, location, rotation, scale, EAttachLocation::KeepRelativeOffset, true, ENCPoolMethod::None);

			return;
		}
	}

	//Effect At Locaiotn;

	if (!!Particle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(InWorld, Particle, Transform);

		return;
	}

	if (!!Niagara)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(InWorld, Niagara, location, rotation, scale);

		return;
	}
}
