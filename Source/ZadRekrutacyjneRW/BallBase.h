// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Components/WidgetComponent.h"
#include "BallBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class ZADREKRUTACYJNERW_API ABallBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallBase();


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
		UWidgetComponent* InteractionWidget;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BallMesh;

};
