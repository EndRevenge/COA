// Fill out your copyright notice in the Description page of Project Settings.


#include "COAMyActor.h"

// Sets default values
ACOAMyActor::ACOAMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(
		CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

}

// Called when the game starts or when spawned
void ACOAMyActor::BeginPlay()
{
	Super::BeginPlay();
	Count = 0;
	
}

// Called every frame
void ACOAMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Count++;
	
	UE_LOG(LogTemp, Warning, TEXT("Count: %d"), Count);

	//

	GEngine->AddOnScreenDebugMessage(0, 0.1f, FColor::White,
		FString::Printf(TEXT("Count: %d"), Count));

}

