// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "ConditionalTypes/Object/Conditional_Object_IsOfClass.h"
#include "Misc/AutomationTest.h"
#include "Mocks/Conditional_MockObject.h"
#include "Mocks/Conditional_MockObjectSecond.h"

BEGIN_DEFINE_SPEC(FConditionalTypeObjectIsOfClassSpec, "SF.Conditional.Types.Object.IsOfClass", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TObjectPtr<SF::UConditional_Object_IsOfClass> Sut = nullptr;
	TObjectPtr<UObject> Object;
END_DEFINE_SPEC(FConditionalTypeObjectIsOfClassSpec)

void FConditionalTypeObjectIsOfClassSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<SF::UConditional_Object_IsOfClass>();
		Object = NewObject<UConditional_MockObject>();
	});
	Describe("using pre-loaded class", [this]
	{
		BeforeEach([this]
		{
			Sut->SetPreLoadedClassToCheckFor(UConditional_MockObject::StaticClass());
		});
		Describe("with test object of correct class", [this]
		{
			It("should yield a yes answer", [this]
			{
				Object = NewObject<UConditional_MockObject>();
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), SF::Conditional::Answer::Yes());
			});
		});
		Describe("with test object of incorrect class", [this]
		{
			It("should yield a no answer", [this]
			{
				Object = NewObject<UConditional_MockObjectSecond>();
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), SF::Conditional::Answer::No());
			});
		});
	});
	
	Describe("using sync-loaded class", [this]
	{
		BeforeEach([this]
		{
			Sut->SetSyncLoadedClassToCheckFor(UConditional_MockObject::StaticClass());
		});
		Describe("with test object of correct class", [this]
		{
			It("should yield a yes answer", [this]
			{
				Object = NewObject<UConditional_MockObject>();
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), SF::Conditional::Answer::Yes());
			});
		});
		Describe("with test object of incorrect class", [this]
		{
			It("should yield a no answer", [this]
			{
				Object = NewObject<UConditional_MockObjectSecond>();
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), SF::Conditional::Answer::No());
			});
		});
	});
}

#endif WITH_AUTOMATION_WORKER