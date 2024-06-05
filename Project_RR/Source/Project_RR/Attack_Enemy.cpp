// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack_Enemy.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Project_RRCharacter.h"

// Sets default values
AAttack_Enemy::AAttack_Enemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(35.f);
	SphereComponent->SetSimulatePhysics(true);
	//Simulation generates Hit events
	SphereComponent->SetNotifyRigidBodyCollision(true);
	// Listen to the OnComponentHit event by binding it to our function
	//SphereComponent->OnComponentHit.AddDynamic(this, &AAttack_Enemy::OnHit);

	// Set this Sphere Component as the root component,
	// otherwise collision won't behave properly
	RootComponent = SphereComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 1500.f;
}

// Called when the game starts or when spawned
void AAttack_Enemy::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentHit.AddDynamic(this, &AAttack_Enemy::OnHit);

	SetLifeSpan(0.15f);
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
	if (Cast<AProject_RRCharacter>(OtherActor) != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Attacked")));
		Destroy();
	}
	
}