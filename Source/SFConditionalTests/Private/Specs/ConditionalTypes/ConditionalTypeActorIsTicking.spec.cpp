// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "ConditionalTypes/Actor/Conditional_Actor_IsTicking.h"
#include "Misc/AutomationTest.h"
#include "Mocks/Conditional_MockActor.h"
#include "Mocks/Conditional_MockObject.h"
#include "TestWorld/AutomationTestWorld.h"

using namespace SF::Conditional;

BEGIN_DEFINE_SPEC(FConditionalTypesActorIsTickingSpec, "SF.Conditional.Types.Actor.IsTicking", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TSharedPtr<WeekendUtils::FScopedAutomationTestWorld> TestWorld;
	TObjectPtr<UObject> Object;
	TObjectPtr<AActor> Actor;
	TObjectPtr<UActorComponent> ActorComponent;
	TObjectPtr<SF::UConditional_Actor_IsTicking> Sut = nullptr;
END_DEFINE_SPEC(FConditionalTypesActorIsTickingSpec)

void FConditionalTypesActorIsTickingSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<SF::UConditional_Actor_IsTicking>();
		Object = NewObject<UConditional_MockObject>();
	});
	
	Describe("with UObject as TestObject", [this]
	{
		It("should yield NoActor error state", [this]
		{
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Error::TestObject::NoActorProvider(Object));
		});
	});
	
	Describe("with AActor as TestObject", [this]
	{
		BeforeEach([this]
		{
			TestWorld = MakeShared<WeekendUtils::FScopedAutomationTestWorld>("TestWorld");
			TestWorld->InitializeGame();
			Actor = TestWorld->AsRef().SpawnActor<AConditional_MockActor>();
		});
		AfterEach([this]
		{
			TestWorld.Reset();
		});
		
		Describe("ticking", [this]
		{
			It("should yield answer Yes", [this]
			{
				Actor->SetActorTickEnabled(true);
				TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::Yes());
			});
		});
		Describe("not ticking", [this]
		{
			It("should yield answer No", [this]
			{
				Actor->SetActorTickEnabled(false);
				TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::No());
			});
		});
	});
}

#endif WITH_AUTOMATION_WORKER