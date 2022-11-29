// Fill out your copyright notice in the Description page of Project Settings.


#include "COAAvatar.h"

ACOAAvatar::ACOAAvatar() :
MaxStamina(100.0f),
Stamina(50.0f),
RunSpeed(900.0f),
StaminaGainRate(16.0f),
StaminaDrainRate(8.0f),
bRunning(false),
bStaminaDrained(false),
MovementScale(1.0f)

{
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mSpringArm ->SetupAttachment(RootComponent);
	mSpringArm->TargetArmLength = 300.0f;

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	mCamera->SetupAttachment(mSpringArm, USpringArmComponent::SocketName);

	mCamera->bUsePawnControlRotation = false;
	mSpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->JumpZVelocity = 600.0f;

}

// Called when the game starts or when spawned
void ACOAAvatar::BeginPlay()
{
	Super::BeginPlay();
}

void ACOAAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	float currentSpeed = WalkSpeed;

	if (GetCharacterMovement()->MovementMode==EMovementMode::MOVE_Walking)
	{

		if (bRunning && !bStaminaDrained)
		{
			//Walking or Waiting
			Stamina = FMath::Max(0.0f, Stamina - StaminaDrainRate * DeltaTime);

			if (Stamina == 0.0f)
			{
				bStaminaDrained = true;
				UpdateMovementParams();
			}
		}
		else
		{
			Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);
			if (Stamina >= MaxStamina)
			{
				bStaminaDrained = false;
				UpdateMovementParams();
			}
		}

	}

	//Set Player Speed
	//GetCharacterMovement()->MaxWalkSpeed = currentSpeed;
		GEngine->AddOnScreenDebugMessage(0, DeltaTime * 2.0f, FColor::Yellow, FString::Printf(TEXT("Tired?: %d Stamina: %f"), bStaminaDrained, Stamina));

		//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Tired?: %d Stamina: %f"), 0, Stamina));
		//Stamina = FMath::Min(MaxStamina, Stamina - StaminaDrainRate * DeltaTime);

	//Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);
	//Stamina= FMath::Min(MaxStamina, Stamina - StaminaDrainRate * DeltaTime);


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

void ACOAAvatar::MoveForward(float value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, value * MovementScale);
	
}

void ACOAAvatar::MoveRight(float value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, value * MovementScale);
	
}

void ACOAAvatar::UpdateMovementParams()
{
	GetCharacterMovement()->MaxWalkSpeed = bRunning && !bStaminaDrained ? RunSpeed : WalkSpeed;
	
}

void ACOAAvatar::ChangeRunPressedStateServer_Implementation(bool pressed)
{
	ChangeRunPressedStateMulti(pressed);
}

void ACOAAvatar::ChangeRunPressedStateMulti_Implementation(bool pressed)
{
	bRunning= pressed;
	UpdateMovementParams();
}

void ACOAAvatar::RunPressed()
{

	ChangeRunPressedStateServer(true);
	
	/*	bRunning = true;
		UpdateMovementParams();
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed; */
}

void ACOAAvatar::RunReleased()
{
	ChangeRunPressedStateServer(false);
	
	/*GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bRunning = false;
	UpdateMovementParams(); */ 
}





