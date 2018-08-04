// Fill out your copyright notice in the Description page of Project Settings.
#include "TankBarrel.h"
#include "Engine/World.h"

/*::Elevate(float RelativeSpeed)

{

	// Move the barrel the right amount this frame

	// Given a max elevation speed, and the frame time

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0, 0));

}*/

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = (FMath::Clamp<float>(RelativeSpeed, -1, +1));
	auto ElevateChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + ElevateChange;

	

	SetRelativeRotation(FRotator(FMath::Clamp<float>(RawNewElevation, MinElevateDegree, MaxElevateDegree), 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Barrel Elevate Called"));
}

