// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GetAIControlledTank() || !GetPlayerTank()) {
		return;
	}
	//GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* AIPossessedTank = GetAIControlledTank();
	ATank* PlayerTank = GetPlayerTank();
	if (AIPossessedTank) {
		UE_LOG(LogTemp, Warning, TEXT("%s is possess by the AI controller"), *AIPossessedTank->GetName());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No tank is possess by the AI controller"));
	}

	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Found the playerTank: %s"), *PlayerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank Not found"));
	}
}

ATank * ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	return PlayerTank;
}

