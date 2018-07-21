// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("%s is possess by the controller"), *Tank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No tank is possess by the controller"));
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("hit location : NO"));
	}


}


//Get world location of line trace through cross hhair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation)
{
	//Find the crosshair position in pixel coordinate
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocationOfCrossHair = FVector2D(ViewportSizeX*CrossHairXLocation, 
														ViewportSizeY*CrossHairYLocation);
	FVector CamLookDirection; 
	if (GetLookDirection(ScreenLocationOfCrossHair, CamLookDirection)) {
		GetLookVectorHitLocation(CamLookDirection, HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Hit location : %s"), *HitLocation.ToString());
		return true;
	}
	return false;
}

//Get location and direction of current viewport ( camera)
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		) 
	{
		HitLocation = HitResult.Location;

		UE_LOG(LogTemp, Warning, TEXT("%s is being hit"),*HitResult.GetActor()->GetName());
		return true;
	}
	HitLocation = FVector(0);
	return false;
}
