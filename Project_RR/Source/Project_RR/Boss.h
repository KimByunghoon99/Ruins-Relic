// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Boss.generated.h"

UCLASS()
class PROJECT_RR_API ABoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoss();

	virtual void Destroyed() override; //�ı��� ȣ��Ǵ� �Լ�

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float ThrowingInterval = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float ThrowingDelay = 2.f;

	//The class used to spawn a dodgeball object
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack)
	TSubclassOf<class AAttack_Enemy> AttackClass;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStatusComponent* StatusComponent;

	//�� ĳ������ �ʱⰪ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Health; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float AttackDamage; //���ݷ�

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};

