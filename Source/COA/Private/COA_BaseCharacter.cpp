// Fill out your copyright notice in the Description page of Project Settings.


#include "COA_BaseCharacter.h"

// Sets default values
ACOA_BaseCharacter::ACOA_BaseCharacter() :
	bDead(false),
	Health(100.0f),
	MaxHealth(100.0f),
	HealingRate(5.0f),
	WalkSpeed(300.0f),
	AttackStartupTime(0.5f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

}

// Called when the game starts or when spawned
void ACOA_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACOA_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bDead)
	{
		Health = FMath::Min(MaxHealth, Health + HealingRate * DeltaTime);
	}

	GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Orange, FString::Printf(TEXT("Health: %f"), Health));

}

// Called to bind functionality to input
void ACOA_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

float ACOA_BaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bDead) return 0.0f;

	//Blueprint Event call
	DamageAmount = ModifyDamage(DamageAmount);

	Health -= DamageAmount;
	if (Health <= 0.f)
	{
		bDead = true;
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController != nullptr)
		{
			DisableInput(PlayerController);
			//CharacterDied();
		}		
			CharacterDied();
						
	}
	return 0.0f;
}

void ACOA_BaseCharacter::ChangeAnimState_Implementation(ECharAnimState NewState)
{
	AnimState = NewState;
	if (NewState == ECharAnimState::CAS_ATTACK)
	{
		//Start Timer
		GWorld->GetTimerManager().SetTimer(AttackTimer, this, &ACOA_BaseCharacter::onAttack, AttackStartupTime, false);

	}
	else
	{
		//Clear Timer
		GWorld->GetTimerManager().ClearTimer(AttackTimer);
	}
}

