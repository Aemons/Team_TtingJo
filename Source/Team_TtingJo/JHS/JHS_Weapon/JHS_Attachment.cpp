#include "JHS_Attachment.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/ShapeComponent.h"

AJHS_Attachment::AJHS_Attachment()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);
}

void AJHS_Attachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	TArray<USceneComponent*> children;
	Root->GetChildrenComponents(true, children);

	for (USceneComponent* Child : children)
	{
		UShapeComponent* Shape = Cast<UShapeComponent>(Child);

		if (!!Shape)
		{
			Shape->OnComponentBeginOverlap.AddDynamic(this, &AJHS_Attachment::OnComponentBeginOverlap);
			Shape->OnComponentEndOverlap.AddDynamic(this, &AJHS_Attachment::OnComponentEndOverlap);

			Collisions.Add(Shape);
		}
	}

	OffCollision();

	Super::BeginPlay();
}

void AJHS_Attachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void AJHS_Attachment::AttachToCollision(FName InCollisionName)
{
	for (UShapeComponent* Collision : Collisions)
	{
		if (Collision->GetName() == InCollisionName.ToString())
		{
			Collision->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InCollisionName);
			
			return;
		}
	}
}

void AJHS_Attachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBOdyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());

	if (OnAttachmentBeginOverlap.IsBound())
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter, this, Cast<ACharacter>(OtherActor));
}

void AJHS_Attachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());

	if (OnAttachmentEndOverlap.IsBound())
		OnAttachmentEndOverlap.Broadcast(OwnerCharacter, Cast<ACharacter>(OtherActor));
}

void AJHS_Attachment::OnCollision()
{
	if (OnAttachmentBeginCollision.IsBound())
		OnAttachmentBeginCollision.Broadcast();

	for (UShapeComponent* Shape : Collisions)
		Shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AJHS_Attachment::OffCollision()
{
	if (OnAttachmentEndCollision.IsBound())
		OnAttachmentEndCollision.Broadcast();

	for (UShapeComponent* Shape : Collisions)
		Shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
