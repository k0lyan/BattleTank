// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	InputComponent->BindAction("Turret_clockwise", IE_Pressed, this, &ATank::RotateTurretR);
	InputComponent->BindAction("Turret_ñclockwise", IE_Pressed, this, &ATank::RotateTurretL);
}

void ATank::RotateTurretL()
{
	UE_LOG(LogTemp, Warning, TEXT("LEFT"))
	Turret->SetRelativeRotation(FRotator(0.f, -45.f, 0.f));
}

void ATank::RotateTurretR()
{
	UE_LOG(LogTemp, Warning, TEXT("RIGHT"))
	Turret->SetRelativeRotation(FRotator(0.f, 45.f, 0.f));
}

void ATank::SetTurretChildActor(UChildActorComponent * TurretFromBP)
{
	Turret = TurretFromBP;
}

