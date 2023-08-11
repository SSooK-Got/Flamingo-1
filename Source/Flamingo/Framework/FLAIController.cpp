#include "FLAIController.h"
#include "EngineUtils.h"

AFLAIController::AFLAIController()
{
}

void AFLAIController::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Move, this, &ThisClass::MyMove, 3.0f, true);
}

void AFLAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Move);
}

void AFLAIController::MyMove()
{
	AActor* TargetActor = nullptr;
	if (FindOrb(TargetActor))
	{
		FAIMoveRequest MoveReq;
		MoveReq.SetUsePathfinding(true);
		MoveReq.SetAcceptanceRadius(5.0f);
		MoveReq.SetReachTestIncludesAgentRadius(false);
		MoveReq.SetGoalActor(TargetActor);
		MoveTo(MoveReq);
	}
}

void AFLAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	//MyMove();
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