// Fill out your copyright notice in the Description page of Project Settings.

#include "MortalAimingComponent.h"
#include "Engine/World.h"

void UMortalAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank) {
		AimAt(PlayerTank->GetActorLocation());

		//Fire if lock
		if (GetFiringStatus() == EFiringStatus::LOCKING) {
			Fire();
		}
	}

	auto Ownername = GetOwner()->GetName();
}




