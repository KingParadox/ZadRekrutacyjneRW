// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "BallBase.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

/////////////////////////////////////// Constructor
AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	InteractionBox->SetupAttachment(RootComponent);

	EquippedBall = nullptr;
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

}

/////////////////////////////////////// Begin Play
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}


/////////////////////////////////////// Player Input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyCharacter::OnInteract);
	PlayerInputComponent->BindAction("ThrowBall", IE_Pressed, this, &AMyCharacter::InitBallThrow);
	PlayerInputComponent->BindAction("ThrowBall", IE_Released, this, &AMyCharacter::TryBallThrow);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

/////////////////////////////////////// Tick
void AMyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bAiming == true)
	{
		bUseControllerRotationYaw = true;

	}
	else
	{
		bUseControllerRotationYaw = false;
	}

	TArray<AActor*>OverlappingActors;

	InteractionBox->GetOverlappingActors(OverlappingActors);

	if (OverlappingActors.Num() == 0)
	{
		if (Interface)
		{
			Interface->HideInteractionWidget();
			Interface = nullptr;
		}
		return;
	}
	AActor* ClosestActor = OverlappingActors[0];

	for (auto CurrentActor : OverlappingActors) 
	{
		if (GetDistanceTo(CurrentActor) < GetDistanceTo(ClosestActor))
		{
			ClosestActor = CurrentActor;
		}

	}

	if (Interface)
	{
		Interface->HideInteractionWidget();
	}
	Interface = Cast<IInteractInterface>(ClosestActor);

	if (Interface)
	{
		Interface->ShowInteractionWidget();
	}


	

}

/////////////////////////////////////// On Interact
void AMyCharacter::OnInteract()
{
	if (Interface)
	{
		Interface->Interact();
	}
}

void AMyCharacter::InitBallThrow()
{
	if (EquippedBall != nullptr)
	{
		CameraComponent->bUsePawnControlRotation = true;
		bAiming = true;
	}

}

void AMyCharacter::TryBallThrow()
{
	CameraComponent->bUsePawnControlRotation = false;
	bAiming = false;
	if (EquippedBall !=nullptr)
	{
		ABallBase* BallBase = Cast<ABallBase>(EquippedBall);
		if (BallBase != nullptr)
		{
			BallBase->ThrowBall();
			EquippedBall = nullptr;
		}
	}
}
