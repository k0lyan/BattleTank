// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* possesedTank = GetControlledTank();

	if (possesedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI name: %s"), *(possesedTank->GetName()))
	}

	ATank* playerTank = GetPlayerTank();

	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI found player: %s"), *(playerTank->GetName()))
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playerTank = GetPlayerTank();
	if (playerTank)
	{
		GetControlledTank()->AimAt(playerTank->GetActorLocation());
	}
	
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerPawn) { return nullptr; }
	return Cast<ATank>(playerPawn);
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}