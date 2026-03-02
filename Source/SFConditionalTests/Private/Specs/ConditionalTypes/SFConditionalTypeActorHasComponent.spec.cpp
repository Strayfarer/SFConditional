// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "ConditionalTypes/Actor/SFConditional_Actor_HasComponent.h"
#include "Misc/AutomationTest.h"
#include "Mocks/SFConditional_MockActor.h"
#include "Mocks/SFConditional_MockActorComponent.h"
#include "Mocks/SFConditional_MockActorComponentSecond.h"
#include "Mocks/SFConditional_MockObject.h"
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
		Sut->SetComponentClass(USFConditional_MockActorComponent::StaticClass());
		Object = NewObject<USFConditional_MockObject>();
	});
	
	Describe("with UObject as TestObject", [this]
	{
		It("should yield NoActor error state", [this]
		{
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Error::TestObject::NoActor(Object));
		});
	});
	
	Describe("with AActor as TestObject", [this]
	{
		BeforeEach([this]
		{
			TestWorld = MakeShared<WeekendUtils::FScopedAutomationTestWorld>("TestWorld");
			TestWorld->InitializeGame();
			Actor = TestWorld->AsRef().SpawnActor<ASFConditional_MockActor>();
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
				ActorComponent = Actor->AddComponentByClass(USFConditional_MockActorComponentSecond::StaticClass(), false, {}, false);
				TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::No());
			});
		});
		Describe("and correct component", [this]
		{
			It("should yield answer Yes", [this]
			{
				ActorComponent = Actor->AddComponentByClass(USFConditional_MockActorComponent::StaticClass(), false, {}, false);
				TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::Yes());
			});
		});
	});
}

#endif WITH_AUTOMATION_WORKER