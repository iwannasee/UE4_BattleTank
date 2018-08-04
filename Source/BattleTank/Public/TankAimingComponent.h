// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"


/*
UENUM()

enum class EFiringState : uint8

{

	Reloading,

	Aiming,

	Locked

};



// Forward Declaration

class UTankBarrel;

class UTankTurret;



// Holds barrel's properties and Elevate method

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class BATTLETANK_API UTankAimingComponent : public UActorComponent

{

	GENERATED_BODY()



public:

	UFUNCTION(BlueprintCallable, Category = "Setup")

		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);



	void AimAt(FVector HitLocation);



protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")

		EFiringState FiringState = EFiringState::Locked;



private:

	// Sets default values for this component's properties

	UTankAimingComponent();



	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;



	UPROPERTY(EditDefaultsOnly, Category = "Firing")

		float LaunchSpeed = 4000;



	void MoveBarrelTowards(FVector AimDirection);

};*/



//Forward Declaration
class UTankBarrel;
class UTankTurret;

//Enum for aim crosshair status
UENUM()
enum class EFiringStatus : uint8 {
	RELOADING,
	AIMING,
	LOCKING
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation) const;

protected:
	UPROPERTY(BlueprintReadOnly)
	EFiringStatus FiringStatus = EFiringStatus::LOCKING;
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void AimingInitialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);
	void MoveBarrelTowards(FVector AimDir) const;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	//TODO remove after aiming component is removed
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 7000.f;

};

