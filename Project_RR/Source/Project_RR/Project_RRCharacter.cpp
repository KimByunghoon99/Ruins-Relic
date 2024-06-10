// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_RRCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "PlayerInstance.h"
#include "StatusComponent.h"
#include "Enemy_Dummy.h"


//////////////////////////////////////////////////////////////////////////
// AProject_RRCharacter

AProject_RRCharacter::AProject_RRCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 1200.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength =700.0f; // The camera follows at this distance behind the character	
	CameraBoom->SetRelativeRotation(FRotator(-65.f, 0.f, 0.f));
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Health = 100.0f;
	MaxHealth = Health;

	AttackDamage = 20.0f; 
	AttackSpeed = 1.0f; 
	DodgeCoolDown = 4.0f; 
	WhirlwindCoolDown = 20.0f;
	TornadoCoolDown = 30.0f;
}

void AProject_RRCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	LoadStatsFromGameInstance();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProject_RRCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProject_RRCharacter::Move);

	}

}

void AProject_RRCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProject_RRCharacter::OnAttackOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		UStatusComponent* StatusComp = OtherActor->FindComponentByClass<UStatusComponent>();
		if (StatusComp)
		{
			StatusComp->LoseHealth(AttackDamage, this);
		}
	}
}


float AProject_RRCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (StatusComponent)
	{
		StatusComponent->LoseHealth(ActualDamage, DamageCauser);
	}

	return ActualDamage;
}


void AProject_RRCharacter::IncreaseRandomStat()
{
	RandomStat = FMath::RandRange(0, 5); 
	if (RandomStat == 0)
	{
		// ü�� ����
		int32 HealthIncreaseInt = FMath::RandRange(10, 20);
		float HealthIncrease = static_cast<float>(HealthIncreaseInt);
		MaxHealth += HealthIncrease;
		Health = MaxHealth;
	}
	else if (RandomStat == 1)
	{
		// ���ݷ� ����
		int32 AttackIncreaseInt = FMath::RandRange(2, 5);
		float AttackIncrease = static_cast<float>(AttackIncreaseInt);
		AttackDamage += AttackIncrease;
	}
	else if (RandomStat == 2)
	{
		//���� �ӵ� ����
		AttackSpeed += 0.25f;
	}

	else if (RandomStat == 3)
	{
		//������ ��Ÿ�� ����
		DodgeCoolDown -= 0.5f;
	}
	else if (RandomStat == 4)
	{
		//������ ��Ÿ�� ����
		WhirlwindCoolDown -= 5.0f;
	}
	else if (RandomStat == 5)
	{
		//����̵� ��Ÿ�� ����
		TornadoCoolDown -= 5.0f;
	}
}

void AProject_RRCharacter::SaveStatsToGameInstance()
{
	UPlayerInstance* GameInstance = Cast<UPlayerInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->PlayerMaxHealth = MaxHealth;
		GameInstance->PlayerHealth = Health;
		GameInstance->PlayerAttackDamage = AttackDamage;
		GameInstance->PlayerAttackSpeed = AttackSpeed;
		GameInstance->PlayerDodgeCool = DodgeCoolDown;
		GameInstance->PlayerWhirlwindCool = WhirlwindCoolDown;
		GameInstance->PlayerTornadoCool = TornadoCoolDown;
	}
}

void AProject_RRCharacter::LoadStatsFromGameInstance()
{
	UPlayerInstance* GameInstance = Cast<UPlayerInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		MaxHealth = GameInstance->PlayerMaxHealth;
		Health = GameInstance->PlayerHealth;
		AttackDamage = GameInstance->PlayerAttackDamage;
		AttackSpeed = GameInstance->PlayerAttackSpeed;
		DodgeCoolDown = GameInstance->PlayerDodgeCool;
		WhirlwindCoolDown = GameInstance->PlayerWhirlwindCool;
	    TornadoCoolDown = GameInstance->PlayerTornadoCool;
	}
}