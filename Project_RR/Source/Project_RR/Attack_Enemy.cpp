// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack_Enemy.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Project_RRCharacter.h"
#include "StatusComponent.h"

// Sets default values
AAttack_Enemy::AAttack_Enemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(20.f);
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);

	RootComponent = SphereComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 1500.f;
}

// Called when the game starts or when spawned
void AAttack_Enemy::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentHit.AddDynamic(this, &AAttack_Enemy::OnHit);

	SetLifeSpan(LifeSpan);
}

// Called every frame
void AAttack_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAttack_Enemy::OnHit(UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	AProject_RRCharacter* PlayerCharacter = Cast<AProject_RRCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// 플레이어의 StatusComponent를 찾아 체력을 감소시킨다.
		UStatusComponent* StatusComp = PlayerCharacter->FindComponentByClass<UStatusComponent>();
		if (StatusComp)
		{
			StatusComp->LoseHealth(AttackDamage, this);
		}
		Destroy();
	}
}