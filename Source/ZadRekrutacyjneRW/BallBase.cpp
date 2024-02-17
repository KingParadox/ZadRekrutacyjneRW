// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBase.h"

// Sets default values
ABallBase::ABallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = _RootComponent;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball mesh"));
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetupAttachment(RootComponent);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction widget"));
	InteractionWidget->SetVisibility(false);
	InteractionWidget->SetupAttachment(BallMesh);
}


// Called every frame
void ABallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallBase::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Take Ball"));
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

