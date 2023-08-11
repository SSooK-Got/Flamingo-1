// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FLAMINGO_API AFLPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFLPlayerController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	void OnPrimaryAction_Pressed();
	void OnPrimaryAction_Released();

private:
	bool bUpdateMovement = false;
};
