// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
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
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("Sight Source"));
	SightSource->SetupAttachment(RootComponent);

	AttackDamage = 10.0f;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Fetch the character currently being controlled by the player
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	// Look at the player character every frame
	bCanSeePlayer = LookAtActor(PlayerCharacter);

	bPreviousCanSeePlayer = bCanSeePlayer;

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnemy::LookAtActor(AActor* TargetActor)
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

		double distance = FVector::Dist(this->GetActorLocation(), TargetActor->GetActorLocation());

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), distance));

		if (distance < 500 && IsAttacking == false)
		{
			FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
			AddMovementInput(Direction, 0.5);
		}

		if (distance < 150)
		{
			FOutputDeviceNull Ar;
			CallFunctionByNameWithArguments(TEXT("AttackStart"), Ar, nullptr, true);
		}

		if (AttackBall == true)
		{
			Melee();
		}
		AttackBall = false;
		return true;
	}
	return false;

}

void AEnemy::Melee()
{
	if (AttackClass == nullptr)
	{
		return;
	}

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 10.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

	//Spawn new dodgeball
	AAttack_Enemy* Projectile = GetWorld()->SpawnActorDeferred<AAttack_Enemy>(AttackClass, SpawnTransform);


	Projectile->GetProjectileMovementComponent()->InitialSpeed = 1000.f;
	Projectile->FinishSpawning(SpawnTransform);

}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (StatusComponent)
	{
		StatusComponent->LoseHealth(ActualDamage, DamageCauser);
	}

	return ActualDamage;
}

void AEnemy::Destroyed()
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