// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (PlayerTank && ControlledTank) {
		//TODO Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);

		//Aim towards the player
		if (!ensure(TankAimComponent)) {
			return;
		} 
		
		TankAimComponent->AimAt(PlayerTank->GetActorLocation());

		//Fire if lock
		if (TankAimComponent->GetFiringStatus() == EFiringStatus::LOCKING) {
			TankAimComponent->Fire();
		}


	}

}


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetPawn();
	TankAimComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn()) { return; }

	GetPawn()->DetachFromControllerPendingDestroy();
}

