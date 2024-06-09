// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Portal.h"
#include "Project_RRGameMode.h"
#include "Project_RRCharacter.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);


}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	;
}


void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AProject_RRCharacter::StaticClass())) 
	{
		UGameplayStatics::OpenLevel(this, LevelName);
	}
}



