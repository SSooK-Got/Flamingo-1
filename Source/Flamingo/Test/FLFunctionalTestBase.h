#pragma once
#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "FLFunctionalTestBase.generated.h"

UCLASS()
class AFLFunctionalTestBase : public AFunctionalTest
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void NextStep();

	UFUNCTION(BlueprintCallable, Category = "Asserts", meta = (HidePin = "ContextObject", DefaultToSelf = "ContextObject"))
	virtual bool AssertAllTrue(const TArray<bool>& Conditions, const FString& Message, const UObject* ContextObject = nullptr);

protected:
	AFLFunctionalTestBase();
	virtual void StartTest() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void FinishTest(EFunctionalTestResult TestResult, const FString& Message) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Cleanup Test"))
	void ReceiveCleanupTest();

private:
	void InternalNextStep();
	bool ProcessTestStep();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StepInterval = 0.f;

private:
	UPROPERTY(Transient)
	TArray<UFunction*> TestStepFuncs;

	bool bNextStep = false;
	int CurrentStepIndex = -1;
};