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

	// �������� �ʱ� �� ���� �����̾ ����Ʈ
	UPROPERTY(EditDefaultsOnly, Category = Health) // ü��
		float MaxHP = 100.f;
		float Health = 100.f;
		
	UPROPERTY(EditDefaultsOnly, Category = Stamina) // ���¹̳�
		float MaxSP = 100.f;
		float Stamina = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = Damage) // ���ݷ�
		float Damage = 10.f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void LoseHealth(float Amount); // ü�� ����

	void GainMaxHealth(float Amount); // �ִ� ü�� ����

	void LoseStamina(float Amount); // ���¹̳� ����

	void GainMaxStamina(float Amount); // �ִ� ���¹̳� ����
	 
	void DamageUP(float Amount); // ���ݷ� ����
};
