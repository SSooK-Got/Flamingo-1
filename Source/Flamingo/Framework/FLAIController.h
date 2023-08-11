#pragma once

#include "CoreMinimal.h"
#include "Flamingo.h"
#include "AIController.h"
#include "FLAIController.generated.h"

UCLASS()
class FLAMINGO_API AFLAIController : public AAIController
{
	GENERATED_BODY()

public:
	AFLAIController();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	bool FindOrb(AActor*& OutActor);

	void MyMove();
	
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

private:
	FTimerHandle TimerHandle_Move;
};
