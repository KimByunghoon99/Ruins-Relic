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

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("Sight Source"));
	SightSource->SetupAttachment(RootComponent);
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

	/*
	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			//Start throwing dodgeballs
			GetWorldTimerManager().SetTimer(ThrowTimerHandle,
				this,
				&AEnemy::Melee,
				ThrowingInterval,
				true,
				ThrowingDelay);
		}
		else
		{
			//Stop throwing dodgeballs
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}
	*/

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