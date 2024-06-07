// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy_Dummy.generated.h"

UCLASS()
class PROJECT_RR_API AEnemy_Dummy : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AEnemy_Dummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStatusComponent* StatusComponent;

	//적 캐릭터의 초기값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float InitialHealth;

};
