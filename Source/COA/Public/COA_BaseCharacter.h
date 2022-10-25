// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "COA_BaseCharacter.generated.h"

UCLASS()
class COA_API ACOA_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACOA_BaseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
		bool bDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
		float Health;

	UPROPERTY(EditAnywhere, Category = "COA")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
		float HealingRate;

	UPROPERTY(EditAnywhere, Category = "COA")
		float WalkSpeed;

	 


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
		float ModifyDamage(float damage);  

	


};
