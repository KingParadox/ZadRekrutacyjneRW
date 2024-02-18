// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "InteractInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ZADREKRUTACYJNERW_API AMyCharacter : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	AMyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* CameraComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bAiming = false;

protected:

	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);


public:	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* EquippedBall;



private: 
	UPROPERTY(EditAnywhere)
		UBoxComponent* InteractionBox;

	IInteractInterface* Interface;
	AController* PlayerController;


	void OnInteract();
	void InitBallThrow();
	void TryBallThrow();
};
