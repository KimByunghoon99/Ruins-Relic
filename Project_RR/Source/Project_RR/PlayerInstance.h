// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayerInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_RR_API UPlayerInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Player Stats")
    float PlayerMaxHealth;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Player Stats")
    float PlayerHealth;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Player Stats")
    float PlayerAttackDamage;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Player Stats")
    float PlayerAttackSpeed;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Player Stats")
    float PlayerDodgeCool;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Player Stats")
    float PlayerWhirlwindCool;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Player Stats")
    float PlayerTornadoCool;

    UPlayerInstance();
};
