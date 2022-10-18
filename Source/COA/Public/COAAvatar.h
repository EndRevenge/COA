// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COA_BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "COAAvatar.generated.h"

/**
 * 
 */
UCLASS()
class COA_API ACOAAvatar : public ACOA_BaseCharacter
{
	GENERATED_BODY()

public:
	ACOAAvatar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
		UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
		USpringArmComponent* mSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
		float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float StaminaGainRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
		bool bStaminaDrained;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
		bool bRunning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float RunSpeed;



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float value);
	void MoveRight(float value);
	void RunPressed();
	void RunReleased();
	
};
