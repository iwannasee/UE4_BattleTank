// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include"Components/PrimitiveComponent.h"
void UTankTrack::SetThrottle(float Throttle)
{

	//TODO clamp actual throttle value so player cant overdrive
	auto ForceApplied = GetForwardVector()*Throttle*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot =Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent());

	if (TankRoot){
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank root not found"));
	}
	
}


