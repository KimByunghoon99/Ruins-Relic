// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Dummy.h"
#include "StatusComponent.h"

// Sets default values
AEnemy_Dummy::AEnemy_Dummy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));

	InitialHealth = 80.0f;

}

// Called when the game starts or when spawned
void AEnemy_Dummy::BeginPlay()
{
	Super::BeginPlay();

	// BeginPlay에서 StatusComponent의 체력 값을 설정.
	if (StatusComponent)
	{
		StatusComponent->SetHealth(InitialHealth);
	}
	
}

// Called every frame
void AEnemy_Dummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


