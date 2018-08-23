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


	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (MaxAmmo <= 0) {
		FiringStatus = EFiringStatus::OUTOFAMMO;
	}
	else if (FPlatformTime::Seconds() - LastFireTime <= ReloadTimeInSeconds) {
		FiringStatus = EFiringStatus::RELOADING;
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringStatus::AIMING;
	}
	else {
		FiringStatus = EFiringStatus::LOCKING;
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

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
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
	return true;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDir) const
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDir.Rotation();
	auto BarrelDeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(BarrelDeltaRotator.Pitch);
	
	//TODO FIX the barrel from trembling
	if (FMath::Abs( BarrelDeltaRotator.Yaw) > 180.f) {
		Turret->Rotate(180-BarrelDeltaRotator.Yaw);
	}else{
		Turret->Rotate(BarrelDeltaRotator.Yaw);	
	}
}

void UTankAimingComponent::Fire()
{
	
	if (FiringStatus != EFiringStatus::RELOADING) {
		bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
		
		if (isReloaded && bCanShoot  && FiringStatus != EFiringStatus::OUTOFAMMO) {
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

			MaxAmmo = MaxAmmo - 1;
			
		}

	
	}

}

int32 UTankAimingComponent::GetMaxAmmo() const
{
	return MaxAmmo;
}
