// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (LeftTrack && RightTrack) {
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;


}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (LeftTrack && RightTrack) {
		LeftTrack->SetThrottle(-Throw);
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardItention = MoveVelocity.GetSafeNormal();
	VelocityMagnitude = FVector::DotProduct(AIForwardItention, TankForward);
	//IntendMoveForward(VelocityMagnitude);

	auto TurnMagnitude = FVector::CrossProduct(TankForward, AIForwardItention).Z;
	IntendTurnRight(TurnMagnitude);

	//UE_LOG(LogTemp, Warning, TEXT("%s is moving with speed %s"), *TankName, *MoveVelocityString);
}
