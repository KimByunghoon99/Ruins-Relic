// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_RRGameMode.h"
#include "Project_RRCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

AProject_RRGameMode::AProject_RRGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	TotalEnemies = 0;
	DestroyedEnemies = 0;
}
void AProject_RRGameMode::BeginPlay()
{
    Super::BeginPlay();

    //Enemy class를 가진 맵상의 모든 액터 추적
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundEnemies); 
    TotalEnemies = FoundEnemies.Num();

    UE_LOG(LogTemp, Warning, TEXT("Total Enemies: %d"), TotalEnemies);
}

void AProject_RRGameMode::EnemyDestroyed()
{
    DestroyedEnemies++;
    UE_LOG(LogTemp, Warning, TEXT("Destroyed Enemies: %d"), DestroyedEnemies);

    CheckForAllEnemiesDestroyed();
}

void AProject_RRGameMode::CheckForAllEnemiesDestroyed()
{
    if (DestroyedEnemies >= TotalEnemies)
    {
        UE_LOG(LogTemp, Warning, TEXT("All Enemies Destroyed"));

        HandleAllEnemiesDestroyed();
        OnAllEnemiesDestroyed.Broadcast();
    }
}