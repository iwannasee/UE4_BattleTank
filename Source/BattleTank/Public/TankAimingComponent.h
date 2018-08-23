// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"



//Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

//Enum for aim crosshair status
UENUM()
enum class EFiringStatus : uint8 {
	RELOADING,
	AIMING,
	LOCKING,
	OUTOFAMMO
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	EFiringStatus GetFiringStatus() const;
	UFUNCTION(BlueprintCallable, Category = Action)
		void Fire();

	UFUNCTION(BlueprintCallable, Category = Action)
		int32 GetMaxAmmo() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	EFiringStatus FiringStatus = EFiringStatus::RELOADING;
	// Called when the game starts
	virtual void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 MaxAmmo = 3;

private:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void AimingInitialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	bool IsBarrelMoving();
	void MoveBarrelTowards(FVector AimDir) const;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector AimDirection;

	//TODO remove after aiming component is removed
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 7000.f;

	UPROPERTY(EditAnywhere, Category = "Firing")
		bool bCanShoot = true;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	
	double LastFireTime = 0;

};

