// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "ConditionalTypes/Actor/SFConditional_Actor_HasComponent.h"
#include "Misc/AutomationTest.h"
#include "Mocks/MockActor.h"
#include "Mocks/MockActorComponent.h"
#include "Mocks/MockActorComponentSecond.h"
#include "Mocks/MockObject.h"
#include "TestWorld/AutomationTestWorld.h"

using namespace SF::Conditional;

BEGIN_DEFINE_SPEC(FConditionalTypeActorHasComponentSpec, "SF.Conditional.Types.Actor.HasComponent", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TSharedPtr<WeekendUtils::FScopedAutomationTestWorld> TestWorld;
	TObjectPtr<UObject> Object;
	TObjectPtr<AActor> Actor;
	TObjectPtr<UActorComponent> ActorComponent;
	TObjectPtr<USFConditional_Actor_HasComponent> Sut = nullptr;
END_DEFINE_SPEC(FConditionalTypeActorHasComponentSpec)

void FConditionalTypeActorHasComponentSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<USFConditional_Actor_HasComponent>();
		Sut->SetComponentClass(UMockActorComponent::StaticClass());
		Object = NewObject<UMockObject>();
	});
	
	Describe("with UObject as TestObject", [this]
	{
		It("should yield NoActor error state", [this]
		{
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Error::TestObject::NoActor());
		});
	});
	
	Describe("with AActor as TestObject", [this]
	{
		BeforeEach([this]
		{
			TestWorld = MakeShared<WeekendUtils::FScopedAutomationTestWorld>("TestWorld");
			TestWorld->InitializeGame();
			Actor = TestWorld->AsRef().SpawnActor<AMockActor>();
		});
		AfterEach([this]
		{
			TestWorld.Reset();
		});
		
		Describe("and no component", [this]
		{
			It("should yield answer No", [this]
			{
				TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::No());
			});
		});
		Describe("and wrong component", [this]
		{
			It("should yield answer No", [this]
			{
				ActorComponent = Actor->AddComponentByClass(UMockActorComponentSecond::StaticClass(), false, {}, false);
				TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::No());
			});
		});
		Describe("and correct component", [this]
		{
			It("should yield answer Yes", [this]
			{
				ActorComponent = Actor->AddComponentByClass(UMockActorComponent::StaticClass(), false, {}, false);
				TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::Yes());
			});
		});
	});
}

#endif WITH_AUTOMATION_WORKER