// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * DegreeToRotatePerSecond * GetWorld()->GetDeltaSeconds();
	auto NewRotation = RotationChange + RelativeRotation.Yaw;
	
	SetRelativeRotation(FRotator(0, NewRotation, 0));
	//UE_LOG(LogTemp, Warning, TEXT("new rotation of turret: %f"), RelativeRotation.Yaw);
}


