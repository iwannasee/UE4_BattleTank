// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void ATank::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	if (TankAimComponent) {
		TankAimComponent->SetBarrelReference(BarrelToSet);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("aim component not found"));
	}

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

