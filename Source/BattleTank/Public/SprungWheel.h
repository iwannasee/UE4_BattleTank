// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class 	UPhysicsConstraintComponent;
class USphereComponent;
UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	void AddDrivingForce(float ForceToApply);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category  ="Component")
	USphereComponent *ConstraintMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent *Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UPhysicsConstraintComponent* ConstraintComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		UPhysicsConstraintComponent* AxleConstraintComponent = nullptr;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SetupConstrain();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void ApplyForce();

	float TotalForceMagnitudeThisFrame = 0;
};
