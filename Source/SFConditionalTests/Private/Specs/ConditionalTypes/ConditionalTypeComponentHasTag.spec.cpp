// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "ConditionalTypes/Component/Conditional_Component_HasTag.h"
#include "Misc/AutomationTest.h"
#include "Mocks/Conditional_MockActorComponent.h"
#include "Mocks/Conditional_MockObject.h"
#include "TestWorld/AutomationTestWorld.h"

using namespace SF::Conditional;

BEGIN_DEFINE_SPEC(FConditionalTypeComponentHasTagSpec, "SF.Conditional.Types.Component.HasTag", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TSharedPtr<WeekendUtils::FScopedAutomationTestWorld> TestWorld;
	TObjectPtr<UObject> Object;
	TObjectPtr<UConditional_MockActorComponent> Component;
	TObjectPtr<SF::UConditional_Component_HasTag> Sut = nullptr;
	FName TagA = FName("A");
	FName TagB = FName("B");
END_DEFINE_SPEC(FConditionalTypeComponentHasTagSpec)

void FConditionalTypeComponentHasTagSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<SF::UConditional_Component_HasTag>();
	});
	
	Describe("with UObject as TestObject", [this]
	{
		It("should yield NoActorComponent error state", [this]
		{
			Object = NewObject<UConditional_MockObject>();
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Error::TestObject::NoActorComponent(Object));
		});
	});
	
	Describe("with UActorComponent as TestObject", [this]
	{
		BeforeEach([this]
		{
			Component = NewObject<UConditional_MockActorComponent>();
		});
		
		Describe("with conditional tags: none", [this]
		{
			Describe("with component tags: none", [this]
			{
				It("should yield YES answer", [this]
				{
					Component->ComponentTags = {};
					Sut->SetTags({});
					TestEqual("Conditional Answer", Sut->EvaluateObject(Component), Answer::Yes());
				});
			});
			Describe("with component tags: { A }", [this]
			{
				It("should yield YES answer", [this]
				{
					Component->ComponentTags = { TagA };
					Sut->SetTags({});
					TestEqual("Conditional Answer", Sut->EvaluateObject(Component), Answer::Yes());
				});
			});
		});
		
		Describe("with conditional tags: { A }", [this]
		{
			Describe("with component tags: none", [this]
			{
				It("should yield YES answer", [this]
				{
					Component->ComponentTags = {};
					Sut->SetTags({ TagA });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Component), Answer::No());
				});
			});
			Describe("with component tags: { A }", [this]
			{
				It("should yield YES answer", [this]
				{
					Component->ComponentTags = { TagA };
					Sut->SetTags({ TagA });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Component), Answer::Yes());
				});
			});
			Describe("with component tags: { B }", [this]
			{
				It("should yield YES answer", [this]
				{
					Component->ComponentTags = { TagB };
					Sut->SetTags({ TagA });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Component), Answer::No());
				});
			});
			Describe("with component tags: { A, B }", [this]
			{
				It("should yield YES answer", [this]
				{
					Component->ComponentTags = { TagA, TagB };
					Sut->SetTags({ TagA });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Component), Answer::Yes());
				});
			});
		});
		
		Describe("with conditional tags: { A, B }", [this]
		{
			Describe("with component tags: none", [this]
			{
				It("should yield NO answer", [this]
				{
					Component->ComponentTags = {};
					Sut->SetTags({ TagA, TagB });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Component), Answer::No());
				});
			});
			Describe("with component tags: { A }", [this]
			{
				It("should yield YES answer", [this]
				{
					Component->ComponentTags = { TagA };
					Sut->SetTags({ TagA, TagB });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Component), Answer::No());
				});
			});
			Describe("with component tags: { B }", [this]
			{
				It("should yield YES answer", [this]
				{
					Component->ComponentTags = { TagB };
					Sut->SetTags({ TagA, TagB });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Component), Answer::No());
				});
			});
			Describe("with component tags: { A, B }", [this]
			{
				It("should yield YES answer", [this]
				{
					Component->ComponentTags = { TagA, TagB };
					Sut->SetTags({ TagA, TagB });
					TestEqual("Conditional Answer", Sut->EvaluateObject(Component), Answer::Yes());
				});
			});
		});
	});
}

#endif WITH_AUTOMATION_WORKER