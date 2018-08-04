// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine.h"
#include "BattleTank.h"
#include "TankTurret.h"
#include"Public/TankBarrel.h"

#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "Engine/World.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"


// Sets default values for this component's properties
/*
UTankAimingComponent::UTankAimingComponent()

{

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features

	// off to improve performance if you don't need them.

	bWantsBeginPlay = true;

	PrimaryComponentTick.bCanEverTick = false;



	// ...

}



void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)

{

	Barrel = BarrelToSet;

	Turret = TurretToSet;

}



void UTankAimingComponent::AimAt(FVector HitLocation)

{

	if (!ensure(Barrel)) { return; }



	FVector OutLaunchVelocity;

	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity

	(

		this,

		OutLaunchVelocity,

		StartLocation,

		HitLocation,

		LaunchSpeed,

		false,

		0,

		0,

		ESuggestProjVelocityTraceOption::DoNotTrace // Paramater must be present to prevent bug

	);



	if (bHaveAimSolution)

	{

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);

	}

	// If no solution found do nothing

}



void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)

{

	if (!ensure(Barrel) || !ensure(Turret)) { return; }



	// Work-out difference between current barrel roation, and AimDirection

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();

	auto AimAsRotator = AimDirection.Rotation();

	auto DeltaRotator = AimAsRotator - BarrelRotator;



	Barrel->Elevate(DeltaRotator.Pitch);

	Turret->Rotate(DeltaRotator.Yaw);

}
*/

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...

}

void UTankAimingComponent::AimAt(FVector HitLocation) const
{
	if (!Barrel) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);


	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		
	} else{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT(" %f cannot find any solution"), Time);
	}
}

void UTankAimingComponent::AimingInitialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	if (Turret && Barrel) { return; }
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDir) const
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDir.Rotation();
	auto BarrelDeltaRotator = AimAsRotator - BarrelRotation;
	//UE_LOG(LogTemp, Warning, TEXT("Aim As Rot: %s"), *AimAsRotator.ToString());

	Barrel->Elevate(BarrelDeltaRotator.Pitch);
	
	//TODO FIX the barrel from trembling
	Turret->Rotate(BarrelDeltaRotator.Yaw);
}

