// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

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
