// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "ConditionalTypes/Object/SFConditional_Object_IsOfClass.h"
#include "Misc/AutomationTest.h"
#include "Mocks/MockObject.h"
#include "Mocks/MockObjectSecond.h"

BEGIN_DEFINE_SPEC(FConditionalTypeObjectIsOfClassSpec, "SF.Conditional.Types.Object.IsOfClass", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TObjectPtr<USFConditional_Object_IsOfClass> Sut = nullptr;
	TObjectPtr<UObject> Object;
END_DEFINE_SPEC(FConditionalTypeObjectIsOfClassSpec)

void FConditionalTypeObjectIsOfClassSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<USFConditional_Object_IsOfClass>();
		Object = NewObject<UMockObject>();
	});
	Describe("using pre-loaded class", [this]
	{
		BeforeEach([this]
		{
			Sut->SetPreLoadedClassToCheckFor(UMockObject::StaticClass());
		});
		Describe("with test object of correct class", [this]
		{
			It("should yield a yes answer", [this]
			{
				Object = NewObject<UMockObject>();
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), SF::Conditional::Answer::Yes());
			});
		});
		Describe("with test object of incorrect class", [this]
		{
			It("should yield a no answer", [this]
			{
				Object = NewObject<UMockObjectSecond>();
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), SF::Conditional::Answer::No());
			});
		});
	});
	
	Describe("using sync-loaded class", [this]
	{
		BeforeEach([this]
		{
			Sut->SetSyncLoadedClassToCheckFor(UMockObject::StaticClass());
		});
		Describe("with test object of correct class", [this]
		{
			It("should yield a yes answer", [this]
			{
				Object = NewObject<UMockObject>();
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), SF::Conditional::Answer::Yes());
			});
		});
		Describe("with test object of incorrect class", [this]
		{
			It("should yield a no answer", [this]
			{
				Object = NewObject<UMockObjectSecond>();
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), SF::Conditional::Answer::No());
			});
		});
	});
}

#endif WITH_AUTOMATION_WORKER