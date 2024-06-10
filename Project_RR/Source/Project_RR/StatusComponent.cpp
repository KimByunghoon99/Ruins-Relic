// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Enemy.h"
#include "Project_RRCharacter.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

    MaxHealth = 100.0f; // 기본 최대 체력 값
    Health = MaxHealth; // 초기 체력 값을 최대 체력 값으로 설정
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
    
    // BeginPlay에서 현재 체력을 최대 체력 값으로 초기화
    Health = MaxHealth;
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStatusComponent::LoseHealth(float Damage, AActor* DamageCauser)
{
	Health -= Damage;
	
	if (Health <= 0.f)
	{
        Health = 0.0f;

        if (DamageCauser)
        {
            if (DamageCauser->IsA(AEnemy::StaticClass()))
            {
                UE_LOG(LogTemp, Warning, TEXT("Killed by Enemy"));
                // 플레이어가 적에 의해 사망
            }
            else if (DamageCauser->IsA(AProject_RRCharacter::StaticClass()))
            {
                UE_LOG(LogTemp, Warning, TEXT("Killed by Player"));
                // 적이 플레이어에 의해 사망
                GetOwner()->Destroy();
            }
        }
    }
    else
    {
        if (DamageCauser)
        {
            if (DamageCauser->IsA(AEnemy::StaticClass()))
            {
                UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
            }
        }
	}
}


void UStatusComponent::SetHealth(float NewHealth)
{
	Health = NewHealth;
}

