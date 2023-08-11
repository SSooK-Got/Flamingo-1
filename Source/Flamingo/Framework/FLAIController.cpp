#include "FLAIController.h"
#include "EngineUtils.h"

AFLAIController::AFLAIController()
{
}

void AFLAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AFLAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

bool AFLAIController::FindOrb(AActor*& OutActor)
{
	static const FName NAME_Orb(TEXT("Orb"));

	TArray<AActor*> Actors;
	
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->ActorHasTag(NAME_Orb))
		{
			Actors.Add(Actor);
		}
	}

	if (Actors.Num() > 0)
	{
		// TODO_glenn : random item in Actors
		OutActor = Actors[0];
		return true;
	}

	OutActor = nullptr;
	return false;
}
