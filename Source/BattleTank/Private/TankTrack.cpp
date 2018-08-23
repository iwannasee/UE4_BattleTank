// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"
#include"Components/PrimitiveComponent.h"

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<ASprungWheel*> UTankTrack::GetWheel() const
{
	//TODO fix from here

	TArray<ASprungWheel*> ResultArrayWheel;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);

		if (!SprungWheel) continue;

		ResultArrayWheel.Add(SprungWheel);
	}
	if (ResultArrayWheel.IsValidIndex(0)) {
		
	}
	
	return ResultArrayWheel;
}

void UTankTrack::SetThrottle(float Throttle)
{

	float CurrentThrottle = FMath::Clamp<float>((Throttle), -1.f, 1.f);
	DriveTrack(CurrentThrottle);

}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle*TrackMaxDrivingForce;
	auto Wheels = GetWheel();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* thisWheel : Wheels) {
		thisWheel->AddDrivingForce(ForcePerWheel);
		
	}
}


