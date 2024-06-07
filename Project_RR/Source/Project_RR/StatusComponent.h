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

	// �⺻ ü�� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float MaxHealth;

	// ���� ü�� ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float Health;

	// �⺻ ���¹̳� ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float MaxStamina;

	//���� ���¹̳� ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float Stamina;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ü�� ���� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Status") 	
	void LoseHealth(float Damage);

	// ���¹̳� ���� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Status")
	void LoseStamina(float Amount); 

	UFUNCTION(BlueprintCallable, Category = "Status")
	void SetHealth(float NewHealth);

	UFUNCTION(BlueprintCallable, Category = "Status")
	void SetStamina(float NewStamina);

	UFUNCTION(BlueprintCallable, Category = "Status")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Status")
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Status")
	float GetStamina() const { return Stamina; }

	UFUNCTION(BlueprintCallable, Category = "Status")
	float GetMaxStamina() const { return MaxStamina; }
};
