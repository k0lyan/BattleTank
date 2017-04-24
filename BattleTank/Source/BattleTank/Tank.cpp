// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming component"));
}

void ATank::SetTankChildActor(UChildActorComponent * tankFromBP)
{
	if (!tankFromBP) { return; }
	tank = tankFromBP;
}
void ATank::SetTurretChildActor(UChildActorComponent * TurretFromBP)
{
	if (!TurretFromBP) { return; }
	turret = TurretFromBP;
}
void ATank::SetBarrelChildActor(UChildActorComponent * barrelFromBP)
{
	if (!barrelFromBP) { return; }
	barrel = barrelFromBP;
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

	InputComponent->BindAxis("Rotate_turret", this, &ATank::RotateTurret);
	InputComponent->BindAxis("Incline_barrel", this, &ATank::InclineBarrel);

	InputComponent->BindAxis("Move_tank", this, &ATank::MoveTank);
	InputComponent->BindAxis("Rotate_tank", this, &ATank::RotateTank);
}

void ATank::RotateTurret(float speed)
{
	if (!turret) { return; }
	float turretRotation = turretSpeed * speed * GetWorld()->GetDeltaSeconds();
	turret->AddRelativeRotation(FRotator(0.f, turretRotation, 0.f));
}

void ATank::InclineBarrel(float speed)
{
	if (!barrel) { return; }
	float barrelInclineSpeed = speed* GetWorld()->GetDeltaSeconds() * inclineSpeed;
	barrel->AddRelativeRotation(FRotator(barrelInclineSpeed, 0.f, 0.f));
}

void ATank::MoveTank(float speed)
{
	if (!tank) { return; }
	float moveSpeed = movingSpeed * speed * GetWorld()->GetDeltaSeconds();
	tank->AddRelativeLocation( tank->GetForwardVector() * moveSpeed);
}

void ATank::RotateTank(float speed)
{
	if (!tank) { return; }
	float rotation = speed * rotationSpeed * GetWorld()->GetDeltaSeconds();
	tank->AddRelativeRotation(FRotator(0.f, rotation, 0.f));
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation);
}