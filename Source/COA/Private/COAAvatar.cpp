// Fill out your copyright notice in the Description page of Project Settings.


#include "COAAvatar.h"

ACOAAvatar::ACOAAvatar() :
bRunning(),
bStaminaDrained(),
MaxStamina(100.0f),
Stamina(MaxStamina),
RunSpeed(0),
StaminaGainRate(1.0f),
StaminaDrainRate(1.0f)

{
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mSpringArm ->SetupAttachment(RootComponent);
	mSpringArm->TargetArmLength = 300.0f;

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	mCamera->SetupAttachment(mSpringArm, USpringArmComponent::SocketName);

	mCamera->bUsePawnControlRotation = false;
	mSpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;

}

//Called to bind functionality input
void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACOAAvatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACOAAvatar::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACOAAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACOAAvatar::RunReleased);


}

void ACOAAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
	{
		//Stamina = FMath::Min(MaxStamina, Stamina - StaminaDrainRate * DeltaTime);
	}

		//Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);
		//Stamina= FMath::Min(MaxStamina, Stamina - StaminaDrainRate * DeltaTime);
	

}

void ACOAAvatar::RunPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	bRunning = true;

}


void ACOAAvatar::RunReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bRunning = false;
}

void ACOAAvatar::UpdateMovementParams()
{
	if (bRunning)
	{

	}
}

void ACOAAvatar::MoveForward(float value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, value);
}

void ACOAAvatar::MoveRight(float value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, value);
}
