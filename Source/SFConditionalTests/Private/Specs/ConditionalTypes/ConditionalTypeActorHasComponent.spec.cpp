// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "ConditionalTypes/Actor/Conditional_Actor_HasComponent.h"
#include "Misc/AutomationTest.h"
#include "Mocks/Conditional_MockActor.h"
#include "Mocks/Conditional_MockActorComponent.h"
#include "Mocks/Conditional_MockActorComponentSecond.h"
#include "Mocks/Conditional_MockObject.h"
#include "TestWorld/AutomationTestWorld.h"

using namespace SF::Conditional;

BEGIN_DEFINE_SPEC(FConditionalTypeActorHasComponentSpec, "SF.Conditional.Types.Actor.HasComponent", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TSharedPtr<WeekendUtils::FScopedAutomationTestWorld> TestWorld;
	TObjectPtr<UObject> Object;
	TObjectPtr<AActor> Actor;
	TObjectPtr<UActorComponent> ActorComponent;
	TObjectPtr<SF::UConditional_Actor_HasComponent> Sut = nullptr;
END_DEFINE_SPEC(FConditionalTypeActorHasComponentSpec)

void FConditionalTypeActorHasComponentSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<SF::UConditional_Actor_HasComponent>();
		Sut->SetComponentClass(UConditional_MockActorComponent::StaticClass());
		Object = NewObject<UConditional_MockObject>();
	});
	
	Describe("with no ComponentClass configured", [this]
	{
		It("should yield NoComponentClassSet error state", [this]
		{
			Sut->SetComponentClass(nullptr);
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Error::NoComponentClassSet());
		});
	});
	
	Describe("with UObject as TestObject", [this]
	{
		It("should yield NoActorProvider error state", [this]
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
				ActorComponent = Actor->AddComponentByClass(UConditional_MockActorComponentSecond::StaticClass(), false, {}, false);
				TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::No());
			});
		});
		Describe("and correct component", [this]
		{
			It("should yield answer Yes", [this]
			{
				ActorComponent = Actor->AddComponentByClass(UConditional_MockActorComponent::StaticClass(), false, {}, false);
				TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::Yes());
			});
		});
	});
}

#endif WITH_AUTOMATION_WORKER