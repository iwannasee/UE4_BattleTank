// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine.h"
#include "BattleTank.h"
#include "TankTurret.h"
#include"Public/TankBarrel.h"
#include "Projectile.h"

#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "Engine/World.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	LastFireTime = FPlatformTime::Seconds();

}


void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	
	if (FPlatformTime::Seconds() - LastFireTime <= ReloadTimeInSeconds) {
		UE_LOG(LogTemp, Warning, TEXT("RELOADING"));
		FiringStatus = EFiringStatus::RELOADING;
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringStatus::AIMING;
		
	}
	else {
		FiringStatus = EFiringStatus::LOCKING;
		UE_LOG(LogTemp, Warning, TEXT("LOCKING"));
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
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

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	if (BarrelForward.Equals(AimDirection, 0.01f)) {
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("AIMING"));
	return true;
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

void UTankAimingComponent::Fire()
{
	
	if (FiringStatus != EFiringStatus::RELOADING) {
		bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
		UE_LOG(LogTemp, Warning, TEXT("FIRE!!!!!"));

		if (isReloaded && bCanShoot) {
			//FiringStatus = EFiringStatus::LOCKING;
			if (!ensure(ProjectileBlueprint)) { return; }
			if (!ensure(Barrel)) { return; }
			//Spawn Projectile At socket location
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);

			Projectile->Launch(LaunchSpeed);

			LastFireTime = FPlatformTime::Seconds();
		}
	}
}
