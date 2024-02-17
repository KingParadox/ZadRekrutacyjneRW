// Fill out your copyright notice in the Description page of Project Settings.

#include "ChestBase.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"

// Sets default values
AChestBase::AChestBase()
{
    PrimaryActorTick.bCanEverTick = true;

    _RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
    RootComponent = _RootComponent;

    ChestDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chest Door Mesh"));
    ChestDoor->SetupAttachment(RootComponent);

    SpawnItemPlace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawn Item Place Mesh"));
    SpawnItemPlace->SetupAttachment(RootComponent);
    SpawnItemPlace->SetRelativeLocation(FVector(-93.0f, 0.0f, 115.0f));


    AnimStartLocation = FVector(0.0f, 0.0f, 110.0f);
    AnimEndLocation = AnimStartLocation + FVector(0.0f, 0.0f, 20.0f);

    InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction widget"));
    InteractionWidget->SetVisibility(false);
}


void AChestBase::Interact()
{
    UE_LOG(LogTemp, Warning, TEXT("Interacted"));
    if (!bOpened)
    {
        UE_LOG(LogTemp, Warning, TEXT("Opened Chest"));
        bOpened = true;
        ChestDoor->SetRelativeLocationAndRotation(AnimEndLocation, FRotator(-30.0f, 0.0f, 0.0f));
        if (GetWorld())
        {
            AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnItemPlace->GetComponentLocation(), FRotator::ZeroRotator);
            if (SpawnedActor)
            {
                UE_LOG(LogTemp, Warning, TEXT("Spawned Actor: %s"), *SpawnedActor->GetName());
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Cant Spawn actor"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Couldnt find world"));
        }

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Closed Chest"));
        bOpened = false;
        ChestDoor->SetRelativeLocationAndRotation(AnimStartLocation, FRotator::ZeroRotator);
    }
}

void AChestBase::ShowInteractionWidget()
{
    if (InteractionWidget)
    {
        InteractionWidget->SetVisibility(true);
    }
}

void AChestBase::HideInteractionWidget()
{
    if (InteractionWidget)
    { 
    InteractionWidget->SetVisibility(false);
    }
}


// Called every frame
void AChestBase::Tick(float DeltaTime)
{
}
