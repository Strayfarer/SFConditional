// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "ConditionalTypes/Actor/Conditional_Actor_HasTag.h"
#include "Misc/AutomationTest.h"
#include "Mocks/Conditional_MockActor.h"
#include "Mocks/Conditional_MockActorComponent.h"
#include "Mocks/Conditional_MockObject.h"
#include "TestWorld/AutomationTestWorld.h"

using namespace SF::Conditional;

BEGIN_DEFINE_SPEC(FConditionalTypeActorHasTagSpec, "SF.Conditional.Types.Actor.HasTag", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TSharedPtr<WeekendUtils::FScopedAutomationTestWorld> TestWorld;
	TObjectPtr<UObject> Object;
	TObjectPtr<AActor> Actor;
	TObjectPtr<UConditional_MockActorComponent> Component;
	TObjectPtr<SF::UConditional_Actor_HasTag> Sut = nullptr;
	FName TagA = FName("A");
	FName TagB = FName("B");
END_DEFINE_SPEC(FConditionalTypeActorHasTagSpec)

void FConditionalTypeActorHasTagSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<SF::UConditional_Actor_HasTag>();
	});
	
	Describe("with UObject as TestObject", [this]
	{
		It("should yield NoActorProvider error state", [this]
		{
			Object = NewObject<UConditional_MockObject>();
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Error::TestObject::NoActorProvider(Object));
		});
	});
	
	Describe("with UActorComponent as TestObject and only owner actor having required tag A configured", [this]
	{
		It("should yield YES answer", [this]
		{
			TestWorld = MakeShared<WeekendUtils::FScopedAutomationTestWorld>("TestWorld");
			TestWorld->InitializeGame();
			Actor = TestWorld->AsRef().SpawnActor<AConditional_MockActor>();
			const FTransform Transform = FTransform::Identity;
			Component = Cast<UConditional_MockActorComponent>(Actor->AddComponentByClass
				(
					UConditional_MockActorComponent::StaticClass(), 
					false, Transform, false
				));
			Actor->Tags = { TagA };
			Sut->SetTags({ TagA });
			TestEqual("Conditional Answer", Sut->EvaluateObject(Component), Answer::Yes());
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
		
		Describe("with conditional tags: none", [this]
		{
			Describe("with actor tags: none", [this]
			{
				It("should yield YES answer", [this]
				{
					Actor->Tags = {};
					Sut->SetTags({});
					TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::Yes());
				});
			});
			Describe("with actor tags: { A }", [this]
			{
				It("should yield YES answer", [this]
				{
					Actor->Tags = { TagA };
					Sut->SetTags({});
					TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::Yes());
				});
			});
		});
		
		Describe("with conditional tags: { A }", [this]
		{
			Describe("with actor tags: none", [this]
			{
				It("should yield YES answer", [this]
				{
					Actor->Tags = {};
					Sut->SetTags({ TagA });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::No());
				});
			});
			Describe("with actor tags: { A }", [this]
			{
				It("should yield YES answer", [this]
				{
					Actor->Tags = { TagA };
					Sut->SetTags({ TagA });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::Yes());
				});
			});
			Describe("with actor tags: { B }", [this]
			{
				It("should yield YES answer", [this]
				{
					Actor->Tags = { TagB };
					Sut->SetTags({ TagA });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::No());
				});
			});
			Describe("with actor tags: { A, B }", [this]
			{
				It("should yield YES answer", [this]
				{
					Actor->Tags = { TagA, TagB };
					Sut->SetTags({ TagA });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::Yes());
				});
			});
		});
		
		Describe("with conditional tags: { A, B }", [this]
		{
			Describe("with actor tags: none", [this]
			{
				It("should yield NO answer", [this]
				{
					Actor->Tags = {};
					Sut->SetTags({ TagA, TagB });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::No());
				});
			});
			Describe("with actor tags: { A }", [this]
			{
				It("should yield YES answer", [this]
				{
					Actor->Tags = { TagA };
					Sut->SetTags({ TagA, TagB });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::No());
				});
			});
			Describe("with actor tags: { B }", [this]
			{
				It("should yield YES answer", [this]
				{
					Actor->Tags = { TagB };
					Sut->SetTags({ TagA, TagB });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::No());
				});
			});
			Describe("with actor tags: { A, B }", [this]
			{
				It("should yield YES answer", [this]
				{
					Actor->Tags = { TagA, TagB };
					Sut->SetTags({ TagA, TagB });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Actor), Answer::Yes());
				});
			});
		});
	});
}

#endif WITH_AUTOMATION_WORKER