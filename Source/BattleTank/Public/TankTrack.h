// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to set maximum driving force, and apply force to the tank
 */
class ASprungWheel;

UCLASS(ClassGroup =(Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, Category = Movement)
	void SetThrottle(float Throttle);


	//this is max force per Track
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float TrackMaxDrivingForce = 400000.f; // Assume for 40 tonne tank

protected:
	virtual void BeginPlay() override;
private:
	UTankTrack();

	TArray<ASprungWheel*> GetWheel() const;

	void DriveTrack(float CurrentThrottle);

	float CurrentThrottle = 0; 

};