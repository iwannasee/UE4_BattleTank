// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Classes/PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;


	ConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Constraint Component"));
	SetRootComponent(ConstraintComponent);



	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(ConstraintComponent);

	ConstraintMesh = CreateDefaultSubobject<USphereComponent>(FName("Constraint Mesh"));
	ConstraintMesh->SetupAttachment(Axle);

	AxleConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Constrain"));
	AxleConstraintComponent->SetupAttachment(Axle);


}



// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	ConstraintMesh->SetNotifyRigidBodyCollision(true);

	ConstraintMesh->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetupConstrain();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame = 0;
	}

}

void ASprungWheel::SetupConstrain()
{
	if (!GetAttachParentActor()) {
		return;
	}

	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) {
		return;
	}

	ConstraintComponent->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleConstraintComponent->SetConstrainedComponents(Axle, NAME_None, ConstraintMesh, NAME_None);
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	ConstraintMesh->AddForce(Axle->GetForwardVector()*TotalForceMagnitudeThisFrame);
}

void ASprungWheel::AddDrivingForce(float ForceToApply)
{
	TotalForceMagnitudeThisFrame += ForceToApply;
}

