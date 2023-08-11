// Fill out your copyright notice in the Description page of Project Settings.


#include "FLPlayerController.h"
#include "Flamingo.h"
#include "Kismet/KismetMathLibrary.h"

AFLPlayerController::AFLPlayerController()
{
	bShowMouseCursor = true;
}

void AFLPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* ControlledPawn = GetPawn();
	
	
	if (ControlledPawn) 
	{
		//if (bUpdateMovement) 
		{
			FHitResult HitResult;

			if (GetHitResultUnderCursorByChannel(FLConst::TraceTypeQuery_Visibility, true, HitResult)) {
				FVector From = ControlledPawn->GetActorLocation();
				FVector To = HitResult.Location;
				FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(From, To);
				ControlledPawn->AddMovementInput(Direction);
			}
		}

	}
	
}
