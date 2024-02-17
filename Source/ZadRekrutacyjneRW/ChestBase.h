// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Components/WidgetComponent.h"
#include "ChestBase.generated.h"


UCLASS()
class ZADREKRUTACYJNERW_API AChestBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChestBase();

protected:

	UPROPERTY()
	FVector AnimStartLocation;
	UPROPERTY()
	FVector AnimEndLocation;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;
	

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* _RootComponent;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ChestDoor;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SpawnItemPlace;

	bool bOpened = false;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* InteractionWidget;

};