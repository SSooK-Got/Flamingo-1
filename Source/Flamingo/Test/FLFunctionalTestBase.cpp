#include "FLFunctionalTestBase.h"
#include "Components/BillboardComponent.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(LogFLFunctionalTest, Display, All);

AFLFunctionalTestBase::AFLFunctionalTestBase()
{
	if (UBillboardComponent* Sprite = GetSpriteComponent())
	{
		Sprite->SetVisibility(false);
	}
}

void AFLFunctionalTestBase::StartTest()
{
	Super::StartTest();

	if (UCameraComponent* Camera = Cast<UCameraComponent>(GetComponentByClass(UCameraComponent::StaticClass())))
	{
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			PC->SetViewTarget(this);
		}
	}

	bNextStep = false;
	CurrentStepIndex = -1;

	// Fill TestStepFuncs;
	{
		TMap<FString, UFunction*> FunctionMap;
		for (TFieldIterator<UFunction> FunctionIter(GetClass(), EFieldIteratorFlags::ExcludeSuper); FunctionIter; ++FunctionIter)
		{
			UFunction* Function = *FunctionIter;

			FString FunctionName = Function->GetName();

			if (FunctionName.Contains(TEXT("TestStep_")))
			{
				FunctionMap.Add(FunctionName, Function);
			}
		}

		if (FunctionMap.Num() > 0)
		{
			FunctionMap.KeySort(TLess<FString>());
			FunctionMap.GenerateValueArray(TestStepFuncs);
		}
	}

	if (TestStepFuncs.Num() > 0)
	{
		NextStep();
	}
}

void AFLFunctionalTestBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bNextStep)
	{
		bNextStep = false;
		if (!ProcessTestStep())
		{
			FinishTest(EFunctionalTestResult::Default, TEXT("Test Finished"));
		}
	}
}

void AFLFunctionalTestBase::FinishTest(EFunctionalTestResult TestResult, const FString& Message)
{
	ReceiveCleanupTest();

	Super::FinishTest(TestResult, Message);
}

void AFLFunctionalTestBase::NextStep()
{
	if (StepInterval > 0.f)
	{
		FTimerHandle GotoNextStepTimer;
		GetWorld()->GetTimerManager().SetTimer(GotoNextStepTimer, FTimerDelegate::CreateUObject(this, &ThisClass::InternalNextStep), StepInterval, false);
	}
	else
	{
		InternalNextStep();
	}
}

bool AFLFunctionalTestBase::AssertAllTrue(const TArray<bool>& Conditions, const FString& Message, const UObject* ContextObject /*= nullptr*/)
{
	bool bFailed = false;
	for (int32 i = 0; i < Conditions.Num(); ++i)
	{
		if (!Conditions[i])
		{
			LogStep(ELogVerbosity::Error, FString::Printf(TEXT("Assertion failed at [%d]: '%s' for context '%s'"), i, *Message, ContextObject ? *ContextObject->GetName() : TEXT("")));
			bFailed = true;
		}
	}

	if (bFailed)
	{
		return false;
	}
	else
	{
		LogStep(ELogVerbosity::Log, FString::Printf(TEXT("All Assertions passed (%s)"), *Message));
		return true;
	}
}

void AFLFunctionalTestBase::InternalNextStep()
{
	bNextStep = true;
	CurrentStepIndex++;
	if (IsInStep())
	{
		FinishStep();
	}
}

bool AFLFunctionalTestBase::ProcessTestStep()
{
	if (TestStepFuncs.IsValidIndex(CurrentStepIndex))
	{
		UFunction* TestStepFunc = TestStepFuncs[CurrentStepIndex];
		StartStep(TestStepFunc->GetName());
		ProcessEvent(TestStepFunc, nullptr);
		return true;
	}
	else
	{
		return false;
	}
}