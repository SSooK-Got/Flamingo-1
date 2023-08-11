// Fill out your copyright notice in the Description page of Project Settings.


#include "FLPlayerController.h"
#include "Flamingo.h"
#include "Kismet/KismetMathLibrary.h"


AFLPlayerController::AFLPlayerController()
{
	bShowMouseCursor = true;
}

void AFLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	static const FName NAME_PrimaryAction(TEXT("PrimaryAction"));

	// Press
	{
		FInputActionBinding AB(NAME_PrimaryAction, IE_Pressed);
		AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &ThisClass::OnPrimaryAction_Pressed);
		InputComponent->AddActionBinding(AB);
	}
	
	// Release
	{
		FInputActionBinding AB(NAME_PrimaryAction, IE_Released);
		AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &ThisClass::OnPrimaryAction_Released);
		InputComponent->AddActionBinding(AB);
	}
}

void AFLPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		if (bUpdateMovement)
		{
			FHitResult HitResult;
			if (GetHitResultUnderCursorByChannel(FLConst::TraceTypeQuery_Visibility, true, HitResult))
			{
				FVector From = ControlledPawn->GetActorLocation();
				FVector To = HitResult.Location;
				FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(From, To);
				ControlledPawn->AddMovementInput(Direction);
			}
		}
	}
}

void AFLPlayerController::OnPrimaryAction_Pressed()
{
	bUpdateMovement= true;
}

void AFLPlayerController::OnPrimaryAction_Released()
{
	bUpdateMovement = false;
}