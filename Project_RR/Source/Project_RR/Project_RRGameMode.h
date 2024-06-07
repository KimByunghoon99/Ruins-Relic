// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Project_RRGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllEnemiesDestroyed);

UCLASS()
class AProject_RRGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProject_RRGameMode();


protected:
    virtual void BeginPlay() override;

public:

    void EnemyDestroyed(); //적 파괴시 호출되는 함수

    UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
    void HandleAllEnemiesDestroyed(); //모든 적 파괴시 호출되는 함수

   
    UPROPERTY(BlueprintAssignable, Category = "GameMode")
    FOnAllEnemiesDestroyed OnAllEnemiesDestroyed;  // 모든 적이 파괴되었을 때 호출되는 Delegate

private:
    int32 TotalEnemies;
    int32 DestroyedEnemies;

    void CheckForAllEnemiesDestroyed();
};



