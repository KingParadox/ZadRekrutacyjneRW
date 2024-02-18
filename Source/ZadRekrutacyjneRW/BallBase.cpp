// Fill out your copyright notice in the Description page of Project Settings.



#include "BallBase.h"
#include "Runtime/Engine/public/TimerManager.h"

// Sets default values
ABallBase::ABallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = _RootComponent;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball mesh"));
	BallMesh->SetupAttachment(RootComponent);
	BallMesh->SetSimulatePhysics(false);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction widget"));
	InteractionWidget->SetVisibility(false);
	InteractionWidget->SetupAttachment(BallMesh);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ProjectileComponent->InitialSpeed = 2000;
	ProjectileComponent->MaxSpeed = 2000;
	ProjectileComponent->bSimulationEnabled = false;

}


// Called every frame
void ABallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallBase::Interact()
{
	// Cannot solve why Even when disabling physics simulation and delaying attach actor to component, it still dont work so
	// I just disabled physics simulation in constructor as temp fix
	if (BPPlayerCharacter->EquippedBall == nullptr)
	{
		BallMesh->SetSimulatePhysics(false);
		this->SetActorEnableCollision(false);
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &ABallBase::AttachBallToPlayer, 0.1f);
	}
}

void ABallBase::ShowInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(true);
	}
}

void ABallBase::HideInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(false);
	}
}

void ABallBase::ThrowBall()
{

	if (BPPlayerCharacter)
	{
		FVector ForwardVector = BPPlayerCharacter->CameraComponent->GetForwardVector();
		ForwardVector *= 1500.0f;
		UE_LOG(LogTemp, Warning, TEXT("Forward Vector: %s"), *ForwardVector.ToString());
		ProjectileComponent->bSimulationEnabled = true;
		ProjectileComponent->Velocity = ForwardVector;
		this->SetActorEnableCollision(true);
	}
}

void ABallBase::AttachBallToPlayer()
{
	BPPlayerCharacter->EquippedBall = this;
	this->AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "BallSocket");
	UE_LOG(LogTemp, Warning, TEXT("Ball Picked up by: %s"), *PlayerCharacter->GetName());
}

