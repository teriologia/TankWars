// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Player not possesing tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Player Possesing %s"), *(controlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
	

}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}
	FVector HitLocation;
	if (GetSightHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation,LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, OutHitLocation);

	}
	

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector CameraWorldLocation;
	return	DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	else 
	{
		OutHitLocation = FVector(0);
		return false;
	}
}

