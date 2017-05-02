// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController cant find aiming component"))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimCrosshair()
{
	if (!ensure(GetControlledTank())) { return; }
	FVector hitLocation; //out param
	if (GetSightRayHitLocation(hitLocation))
	{
		GetControlledTank()->AimAt(hitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	HitLocation = FVector(1.0);

	//find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D screenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY*CrosshairYLocation);

	FVector lookDirection;

	if (GetLookDirection(screenLocation, lookDirection))
	{
		if (GetLookVectorHitLocation(lookDirection, HitLocation))
		{
			//UE_LOG(LogTemp, Warning, TEXT("hit location: %s"), *(HitLocation.ToString()))
		}


		//if (Hit.bBlockingHit)
		//{
		//	HitLocation = Hit.Location;
		//}
		//return Hit.bBlockingHit;

	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, cameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocaction) const
{
	FHitResult Hit;

	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * lineTraceRange);

	GetWorld()->LineTraceSingleByChannel(
		Hit,        //result
		StartLocation,    //start
		EndLocation, //end
		ECollisionChannel::ECC_Visibility //collision channel
	);

	if (Hit.bBlockingHit)
	{
		HitLocaction = Hit.Location;
	}
	else
	{
		HitLocaction = FVector(0);
	}
	return Hit.bBlockingHit;
}