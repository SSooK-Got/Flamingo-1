// Fill out your copyright notice in the Description page of Project Settings.


#include "FLPlayerController.h"
#include "Flamingo.h"
#include "Kismet/KismetMathLibrary.h"
#include "FLGameMode.h"

AFLPlayerController::AFLPlayerController()
{
	bShowMouseCursor = true;
}

void AFLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	static const FName NAME_PrimaryAction(TEXT("PrimaryAction"));

	// PrimaryAction_Press
	{
		FInputActionBinding AB(NAME_PrimaryAction, IE_Pressed);
		AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &ThisClass::OnPrimaryAction_Pressed);
		InputComponent->AddActionBinding(AB);
	}
	
	// PrimaryAction_Release
	{
		FInputActionBinding AB(NAME_PrimaryAction, IE_Released);
		AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &ThisClass::OnPrimaryAction_Released);
		InputComponent->AddActionBinding(AB);
	}

	static const FName NAME_SpawnOrb(TEXT("SpawnOrb"));
	
	// SpawnOrb_Released
	{
		FInputActionBinding AB(NAME_SpawnOrb, IE_Released);
		AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &ThisClass::OnSpawnOrb_Released);
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

void AFLPlayerController::OnSpawnOrb_Released()
{
	if (GetPawn())
	{
		AFLGameMode* FLGameMode = GetWorld()->GetAuthGameMode<AFLGameMode>();
		check(FLGameMode);

		if (FLGameMode->OrbClass)
		{
			FActorSpawnParameters Params;
			GetWorld()->SpawnActor<AActor>(FLGameMode->OrbClass, GetPawn()->GetActorTransform(), Params);
		}
		else
		{
			UE_LOG(LogFL, Error, TEXT("OrbClass is not specified!"));
		}
	}
}