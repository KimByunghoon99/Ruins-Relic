// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Attack_Enemy.h"
#include "FunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Misc/OutputDeviceNull.h"
#include "StatusComponent.h"
#include "Project_RRGameMode.h"

// Sets default values
ABoss::ABoss()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("Sight Source"));
	SightSource->SetupAttachment(RootComponent);

	AttackDamage = 10.0f;
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Fetch the character currently being controlled by the player
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	// Look at the player character every frame
	bCanSeePlayer = LookAtActor(PlayerCharacter);

	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			GetWorldTimerManager().SetTimer(ThrowTimerHandle,
				this,
				&ABoss::Melee,
				ThrowingInterval,
				true,
				ThrowingDelay);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}

	bPreviousCanSeePlayer = bCanSeePlayer;
}

bool ABoss::LookAtActor(AActor* TargetActor)
{
	if (TargetActor == nullptr) return false;

	const TArray<const AActor*> IgnoreActors = { this, TargetActor };
	if (UFunctionLibrary::CanSeeActor(GetWorld(),
		SightSource->GetComponentLocation(),
		TargetActor,
		IgnoreActors))
	{
		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		// Calculate the necessary rotation for the Start point to face the End point
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		//Set the enemy's rotation to that rotation
		SetActorRotation(LookAtRotation);

		return true;
	}
	return false;

}

void ABoss::Melee()
{
	if (AttackClass == nullptr)
	{
		return;
	}

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 10.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

	FVector ForwardVector2 = GetActorForwardVector();
	float SpawnDistance2 = 10.f;
	FVector SpawnLocation2 = GetActorLocation() + (ForwardVector2 * SpawnDistance2);
	FTransform SpawnTransform2(GetActorRotation() * 1.2, SpawnLocation2);

	FVector ForwardVector3 = GetActorForwardVector();
	float SpawnDistance3 = 10.f;
	FVector SpawnLocation3 = GetActorLocation() + (ForwardVector3 * SpawnDistance3);
	FTransform SpawnTransform3(GetActorRotation() * 0.8, SpawnLocation3);

	AAttack_Enemy* Projectile = GetWorld()->SpawnActorDeferred<AAttack_Enemy>(AttackClass, SpawnTransform);
	AAttack_Enemy* Projectile2 = GetWorld()->SpawnActorDeferred<AAttack_Enemy>(AttackClass, SpawnTransform2);
	AAttack_Enemy* Projectile3 = GetWorld()->SpawnActorDeferred<AAttack_Enemy>(AttackClass, SpawnTransform3);

	Projectile->GetProjectileMovementComponent()->InitialSpeed = 1000.f;
	Projectile->FinishSpawning(SpawnTransform);

	Projectile2->GetProjectileMovementComponent()->InitialSpeed = 1000.f;
	Projectile2->FinishSpawning(SpawnTransform2);

	Projectile3->GetProjectileMovementComponent()->InitialSpeed = 1000.f;
	Projectile3->FinishSpawning(SpawnTransform3);

}

float ABoss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (StatusComponent)
	{
		StatusComponent->LoseHealth(ActualDamage, DamageCauser);
	}

	return ActualDamage;
}

void ABoss::Destroyed()
{
	Super::Destroyed();

	// 게임 모드에 적이 파괴되었음을 알림
	AProject_RRGameMode* GameMode = Cast<AProject_RRGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy Destroyed - Notifying GameMode"));
		GameMode->EnemyDestroyed();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get GameMode"));
	}

}
