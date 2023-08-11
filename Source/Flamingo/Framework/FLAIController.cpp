#include "FLAIController.h"
#include "EngineUtils.h"

AFLAIController::AFLAIController()
{
}

void AFLAIController::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Move, this, &ThisClass::Move, 3.0f, true);
}

void AFLAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Move);
}

void AFLAIController::Move()
{
	AActor* TargetActor = nullptr;
	if (FindOrb(TargetActor))
	{
		UE_LOG(LogFLAI, Display, TEXT("Yeah!!!!! Find Orb!"));
	}
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

	UE_LOG(LogFLAI, Display, TEXT("Cannot Find Orb!"));

	OutActor = nullptr;
	return false;
}
