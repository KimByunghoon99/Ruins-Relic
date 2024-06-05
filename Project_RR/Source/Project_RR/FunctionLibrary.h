// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_RR_API UFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Can we see the given actor
	static bool CanSeeActor(const UWorld* World,
		FVector Location,
		const AActor* TargetActor,
		TArray<const AActor*> IgnoreActors = TArray<const AActor*>());
};
