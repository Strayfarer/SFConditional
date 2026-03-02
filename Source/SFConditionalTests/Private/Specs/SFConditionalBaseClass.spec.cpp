// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "Misc/AutomationTest.h"
#include "Mocks/SFConditional_MockObject.h"
#include "Mocks/SFConditional_MockSFConditional.h"

using namespace SF::Conditional;

BEGIN_DEFINE_SPEC(FConditionalBaseClassSpec, "SF.Conditional.BaseClass", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TObjectPtr<USFConditional_MockSFConditional> Sut = nullptr;
	TObjectPtr<UObject> Object = nullptr;
	FInt32Range ChildRange_OneAllowed = FInt32Range(TRangeBound<int>::Inclusive(1), TRangeBound<int>::Inclusive(1));
END_DEFINE_SPEC(FConditionalBaseClassSpec)

void FConditionalBaseClassSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<USFConditional_MockSFConditional>();
		Object = NewObject<USFConditional_MockObject>();
	});
	Describe("evaluated will invalid test object", [this]
	{
		It("should yield InvalidTestObject error", [this]
		{
			TestEqual("Conditional Answer", 
				Sut->EvaluateObject(nullptr), Answer::Error::InvalidTestObject());
		});
	});
	Describe("answering yes but with 0,7 weight", [this]
	{
		It("should yield a [true | 0,7] answer", [this]
		{
			Sut->Answer = Answer::Yes();
			Sut->SetWeight(0.7f);
			TestEqual("Conditional Answer", 
				Sut->EvaluateObject(Object), Answer::Create(true, 0.7f));
		});
	});
	Describe("answering yes but inverted", [this]
	{
		It("should yield a no answer", [this]
		{
			Sut->Answer = Answer::Yes();
			Sut->SetIsInverted(true);
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::No());
		});
	});
	Describe("answering [true | 0,7] but inverted", [this]
	{
		It("should yield a [false | 0,3] answer", [this]
		{
			Sut->Answer = Answer::Create(true, 0.7f);
			Sut->SetIsInverted(true);
			TestEqual("Conditional Answer", 
				Sut->EvaluateObject(Object), Answer::Create(false, 0.3f));
		});
	});
	Describe("answering no but optional", [this]
	{
		It("should yield a [true | 0,0] answer", [this]
		{
			Sut->Answer = Answer::No();
			Sut->SetIsOptional(true);
			TestEqual("Conditional Answer", 
				Sut->EvaluateObject(Object), Answer::Create(true, 0.0));
		});
	});
	Describe("answering [false | 0,7] but does not impact score on fail", [this]
	{
		It("should yield a No answer", [this]
		{
			Sut->Answer = Answer::Create(false, 0.7f);
			Sut->SetDoesImpactScoreOnFail(false);
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::No());
		});
	});
	Describe("having an invalid child", [this]
	{
		It("should yield HasInvalidChild error state", [this]
		{
			Sut->AllowedChildrenNumRange = ChildRange_OneAllowed;
			Sut->TryAddChild(nullptr);
			TestEqual("Conditional Answer", 
				Sut->EvaluateObject(Object), Answer::Error::HasInvalidChild());
		});
	});
	Describe("allowing 1 child but being configured with 0", [this]
	{
		It("should yield NumChildrenUnsupported error state", [this]
		{
			Sut->AllowedChildrenNumRange = ChildRange_OneAllowed;
			TestEqual("Conditional Answer", 
				Sut->EvaluateObject(Object), Answer::Error::NumChildrenUnsupported());
		});
	});
}

#endif WITH_AUTOMATION_WORKER