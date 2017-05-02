// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelReference(UTankBarrel* barrel);
	void SetTurretReference(UTankTurret* Turret);
	void AimAt(FVector HitLocation, float firingSpeed);

private:
	UTankBarrel* barrel = nullptr;
	void MoveBarrel(FVector);

	UTankTurret* Turret = nullptr;
	void RotateTurret(FVector);

};
