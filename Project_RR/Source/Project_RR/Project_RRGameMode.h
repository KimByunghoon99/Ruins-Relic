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

    void EnemyDestroyed(); //�� �ı��� ȣ��Ǵ� �Լ�

    UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
    void HandleAllEnemiesDestroyed(); //��� �� �ı��� ȣ��Ǵ� �Լ�

   
    UPROPERTY(BlueprintAssignable, Category = "GameMode")
    FOnAllEnemiesDestroyed OnAllEnemiesDestroyed;  // ��� ���� �ı��Ǿ��� �� ȣ��Ǵ� Delegate

private:
    int32 TotalEnemies;
    int32 DestroyedEnemies;

    void CheckForAllEnemiesDestroyed();
};



