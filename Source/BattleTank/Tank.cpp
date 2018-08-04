// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankBarrel.h"

/*
ATank::ATank()

{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = false;

}



void ATank::BeginPlay()

{

	Super::BeginPlay(); // Needed for BP Begin Play to run!

}



void ATank::Fire()

{

	if (!ensure(Barrel)) { return; }

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;



	if (isReloaded)

	{

		// Spawn a projectile at the socket location on the barrel

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(

			ProjectileBlueprint,

			Barrel->GetSocketLocation(FName("Projectile")),

			Barrel->GetSocketRotation(FName("Projectile"))

			);



		Projectile->Launch(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();

	}

}*/



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay();
}


void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	UE_LOG(LogTemp, Warning, TEXT("FIRE!!!!!"));

	if (isReloaded && bCanShoot) {
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
