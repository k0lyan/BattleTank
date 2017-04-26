// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 

	// ...
}


void UTankAimingComponent::SetBarrellreference(UTankBarrel* barrelToSet)
{
	barrel = barrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float firingSpeed)
{
	if (!barrel) { return; }
	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	//Calculate OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		HitLocation,
		firingSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		auto AimDirection = outLaunchVelocity.GetSafeNormal();
		auto tankName = GetOwner()->GetName();
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	auto BarrelRotation = barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	barrel->Elevate(5);
}