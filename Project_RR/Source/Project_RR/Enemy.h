// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class PROJECT_RR_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool AttackBall = false;

	virtual void Destroyed() override; //파괴시 호출되는 함수

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SightSource;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Change the rotation of the character to face the given actor
	bool LookAtActor(AActor* TargetActor);

	void Melee();

	//Whether the enemy can see the player this frame
	bool bCanSeePlayer = false;
	//Whether the enemy could see the player last frame
	bool bPreviousCanSeePlayer = false;

	FTimerHandle ThrowTimerHandle;

	float ThrowingInterval = 0.5f;
	float ThrowingDelay = 0.5f;

	//The class used to spawn a dodgeball object
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack)
	TSubclassOf<class AAttack_Enemy> AttackClass;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStatusComponent* StatusComponent;

	//적 캐릭터의 초기값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float AttackDamage; //공격력

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
