// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Project_RRCharacter.generated.h"


UCLASS(config=Game)
class AProject_RRCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;



public:
	AProject_RRCharacter();

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStatusComponent* StatusComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float AttackDamage; //공격력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float AttackSpeed; // 공격 속도

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float DodgeCoolDown; // 구르기 쿨타임 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float WhirlwindCoolDown; //휠인드 쿨타임

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float TornadoCoolDown; //토네이도 쿨타임


	UPROPERTY(BlueprintReadWrite)
	int32 RandomStat;

	UFUNCTION()
	void OnAttackOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// 체력 또는 공격력 증가 함수
	UFUNCTION(BlueprintCallable)
	void IncreaseRandomStat();

	UFUNCTION(BlueprintCallable)
	void SaveStatsToGameInstance();

	UFUNCTION(BlueprintCallable)
	void LoadStatsFromGameInstance();
};

