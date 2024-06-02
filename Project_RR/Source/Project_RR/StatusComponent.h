// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_RR_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// 소유자의 초기 및 현재 스테이어스 포인트
	UPROPERTY(EditDefaultsOnly, Category = Health) // 체력
		float MaxHP = 100.f;
		float Health = 100.f;
		
	UPROPERTY(EditDefaultsOnly, Category = Stamina) // 스태미나
		float MaxSP = 100.f;
		float Stamina = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = Damage) // 공격력
		float Damage = 10.f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void LoseHealth(float Amount); // 체력 감소

	void GainMaxHealth(float Amount); // 최대 체력 증가

	void LoseStamina(float Amount); // 스태미나 감소

	void GainMaxStamina(float Amount); // 최대 스태미나 증가
	 
	void DamageUP(float Amount); // 공격력 증가
};
