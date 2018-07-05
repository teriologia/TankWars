// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
	}
	else
	{
	}
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (GetPlayerTank())
	{
		
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	/*auto PlayerPawn = GetWorld()->GetFirtsPlayerController()->GetPawn;
	if (!Cast)
	{
		return nullptr;
	}*/

	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
