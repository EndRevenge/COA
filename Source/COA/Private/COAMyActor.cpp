// Fill out your copyright notice in the Description page of Project Settings.


#include "COAMyActor.h"

// Sets default values
ACOAMyActor::ACOAMyActor() :
HitPoints(100)

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(
		CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

}

bool ACOAMyActor::IncreaseCounter(int incAmount, UCameraComponent* CameraComp, float& HealthPercent)
{
	Count += incAmount; // Count = Count + incAmount;

	//Log Version
	UE_LOG(LogTemp, Warning, TEXT("Health: %d"), Count);

	
	GEngine->AddOnScreenDebugMessage(0, 0.1f, FColor::White,
		FString::Printf(TEXT("Health: %d"), HitPoints));
	//UE_LOG(LogTemp, Warning, TEXT("Health: %d"), HitPoints);

	//

	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::White,
		FString::Printf(TEXT("Count: %d"), Count));

	HealthPercent = HitPoints / 100.0f;

	float FinalDamage = ModifyDamageBlueprint(400);

	if (/*camera && HitPoints*/ CameraComp != nullptr) CameraComp->SetFieldOfView(80 + (HitPoints % 40));

	return true;
}

float ACOAMyActor::GetHealthPercent()
{
	return HitPoints / 100.0f;
}

float ACOAMyActor::ModifyDamageBlueprint_Implementation(float Damage)
{
	return Damage;
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
	
}

