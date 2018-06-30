// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Can't Find PlayerTank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI found PlayerTank: %s"), *(PlayerTank->GetName()));
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
