// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f; // 최대 체력 값
	Health = MaxHealth; // 체력 값
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStatusComponent::LoseHealth(float Damage)
{
	Health -= Damage;
	
	if (Health <= 0.f)
	{
		Health = 0.0f;

		GetOwner()->Destroy(); // 체력 0이면 엑터 파괴
	}
}


void UStatusComponent::LoseStamina(float Amount)
{
	Stamina -= Amount;
	
	if (Stamina <= 0.f) 
	{

	}
}

void UStatusComponent::SetHealth(float NewHealth)
{
	Health = NewHealth;
}

void UStatusComponent::SetStamina(float NewStamina)
{
	Stamina = NewStamina;
}
