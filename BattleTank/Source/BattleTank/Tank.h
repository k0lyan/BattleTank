// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetTankChildActor(UChildActorComponent* tankFromBP);

	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetTurretChildActor(UChildActorComponent* TurretFromBP);

	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetBarrelChildActor(UChildActorComponent* TurretFromBP);

	void AimAt(FVector HitLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UChildActorComponent* turret = nullptr;
	UChildActorComponent* barrel = nullptr;
	UChildActorComponent* tank = nullptr;

	void RotateTurret(float);
	void InclineBarrel(float);

	void MoveTank(float speed);
	void RotateTank(float speed);

	UPROPERTY(EditAnywhere)
	float rotationSpeed = 120.f;

	UPROPERTY(EditAnywhere)
	float movingSpeed = 120.f;

	UPROPERTY(EditAnywhere)
	float inclineSpeed = 120.f;

	UPROPERTY(EditAnywhere)
	float turretSpeed = 120.f;
};
