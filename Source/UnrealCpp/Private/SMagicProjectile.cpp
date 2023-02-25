// Fill out your copyright notice in the Description page of Project Settings.

#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"


//Not working for others.
ASMagicProjectile::ASMagicProjectile()
{
	//Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");	//making instances of every component to attach

	//SphereComp->SetCollisionObjectType(ECC_WorldDynamic);					//setting the colision preset and  the ticks manually in cpp
	//SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);				//can set them up in dividual settings like this or in project settings ->collission
	//SphereComp->SetCollisionResponseToAllChannel(ECC_Pawn, ECR_Overlap);		//and connect it using the "Projectile" code below v, that is better

	SphereComp->SetCollisionProfileName("Projectile");		//adding collision preset instead of the set given since they have too much tick boxes to overlap collision hierchy.;
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	RootComponent = SphereComp;								//this will be default

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject <UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.0f);
			Destroy();
		}
	}
}

//Called when the game starts or when spawend
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

//Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
