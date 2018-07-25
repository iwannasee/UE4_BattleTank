// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::EleVate(float RelativeSpeed)
{
	RelativeSpeed = (FMath::Clamp<float>(RelativeSpeed, -1, +1));
	auto ElevateChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + ElevateChange;

	

	SetRelativeRotation(FRotator(FMath::Clamp<float>(RawNewElevation, MinElevateDegree, MaxElevateDegree), 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Barrel Elevate Called"));
}

