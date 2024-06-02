// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatusComponent::LoseHealth(float Amount)
{
	Health -= Amount;
	
	if (Health <= 0.f)
	{

	}
}

void UStatusComponent::GainMaxHealth(float Amount)
{
	MaxHP += Amount;
	Health = MaxHP;
}

void UStatusComponent::LoseStamina(float Amount)
{
	Stamina -= Amount;
	
	if (Health <= 0.f) 
	{

	}
}

void UStatusComponent::GainMaxStamina(float Amount)
{
	Health += Stamina;
	Stamina = MaxSP;
}

void UStatusComponent::DamageUP(float Amount)
{
	Damage += Amount;
}