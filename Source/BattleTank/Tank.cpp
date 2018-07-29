// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankTurret.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect pointers as added at construction
	TankAimComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}



void ATank::AimAt(FVector HitLocation) const
{
	if (TankAimComponent) {
		TankAimComponent->AimAt(HitLocation, LaunchSpeed);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("aim component not found"));
	}

}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (TankAimComponent) {
		TankAimComponent->SetBarrelReference(BarrelToSet);
		Barrel = BarrelToSet;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("aim component not found. could not set up barrel reference"));
	}

}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	if(TankAimComponent) {
		TankAimComponent->SetTurretReference(TurretToSet);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("aim component not found. could not set up turret reference"));
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::Fire()
{
		
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	UE_LOG(LogTemp, Warning, TEXT("FIRE!!!!!"));
	if(!ProjectileBlueprint){ UE_LOG(LogTemp, Warning, TEXT("Fired but there was no projectile")); }
	if (Barrel && isReloaded && bCanShoot) {

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

