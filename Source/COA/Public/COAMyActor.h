// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h" 
#include "Camera/CameraComponent.h"
#include "COAMyActor.generated.h"


UCLASS()
class COA_API ACOAMyActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACOAMyActor();

	//This is the actor's hit points!
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category ="COA", DisplayName="Health")
		int HitPoints;
	
	UPROPERTY()
		UCameraComponent* Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	int Count;


};
