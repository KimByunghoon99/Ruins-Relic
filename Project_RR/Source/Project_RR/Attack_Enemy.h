// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Attack_Enemy.generated.h"

UCLASS()
class PROJECT_RR_API AAttack_Enemy : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:
	// Sets default values for this actor's properties
	AAttack_Enemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float LifeSpan = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UProjectileMovementComponent* GetProjectileMovementComponent() const
	{
		return ProjectileMovement;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AttackDamage;


	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);
};
