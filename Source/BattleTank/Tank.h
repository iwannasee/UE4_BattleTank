// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
/*

// Forward declarations

class UTankBarrel;

class AProjectile;



UCLASS()

class BATTLETANK_API ATank : public APawn

{

	GENERATED_BODY()



public:

	UFUNCTION(BlueprintCallable, Category = "Firing")

		void Fire();



private:

	// Sets default values for this pawn's properties

	ATank();



	virtual void BeginPlay() override;



	UPROPERTY(EditDefaultsOnly, Category = "Setup")

		TSubclassOf<AProjectile> ProjectileBlueprint;



	// TODO remove once firing is moved to aiming component

	UPROPERTY(EditDefaultsOnly, Category = "Firing")

		float LaunchSpeed = 4000;



	UPROPERTY(EditDefaultsOnly, Category = "Firing")

		float ReloadTimeInSeconds = 3;



	// Local barrel reference for spawning projectile

	UTankBarrel* Barrel = nullptr; // TODO Remove



	double LastFireTime = 0;

};
*/


class AProjectile;
class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void virtual BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Action)
		void Fire();

private:

	UPROPERTY(EditAnywhere, Category = "Firing")
		bool bCanShoot = true;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr;
};
