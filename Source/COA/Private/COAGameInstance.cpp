// Fill out your copyright notice in the Description page of Project Settings.


#include "COAGameInstance.h"

void UCOAGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance::Init"));
	
}

void UCOAGameInstance::Host()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("Hosting"));

	GWorld->ServerTravel("/Game/Blueprints/Maps/Lobby?listen");
}

void UCOAGameInstance::Join(FString& Address)
{
	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Yellow, FString::Printf(TEXT("Joining %s"), *Address));

	GWorld->GetFirstPlayerController()->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
