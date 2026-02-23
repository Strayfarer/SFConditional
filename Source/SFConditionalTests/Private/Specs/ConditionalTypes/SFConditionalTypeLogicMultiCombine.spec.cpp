// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "ConditionalTypes/Logic/SFConditional_Logic_MultiCombine.h"
#include "ConditionalTypes/Utility/SFConditional_Utility_AlwaysFalse.h"
#include "ConditionalTypes/Utility/SFConditional_Utility_AlwaysTrue.h"
#include "Misc/AutomationTest.h"
#include "Mocks/MockObject.h"
#include "Mocks/MockSFConditional.h"

using namespace SF::Conditional;

BEGIN_DEFINE_SPEC(FConditionalTypeLogicMultiCombineSpec, "SF.Conditional.Types.Logic.MultiCombine", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TObjectPtr<USFConditional_Logic_MultiCombine> Sut = nullptr;
	TObjectPtr<UObject> Object = nullptr;
END_DEFINE_SPEC(FConditionalTypeLogicMultiCombineSpec)

void FConditionalTypeLogicMultiCombineSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<USFConditional_Logic_MultiCombine>();
		Object = NewObject<UMockObject>();
	});
	
	Describe("with binary rule AND", [this]
	{
		BeforeEach([this]
		{
			Sut->SetAnswerCombineRuleBinary(ESFCombineRuleBinary::And);
		});
		Describe("with two true children", [this]
		{
			It("should yield a yes answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Yes());
			});
		});
		Describe("with one true, one false child", [this]
		{
			It("should yield a no answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::No());
			});
		});
		Describe("with two false children", [this]
		{
			It("should yield a no answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::No());
			});
		});
	});
	
	
	Describe("with binary rule OR", [this]
	{
		BeforeEach([this]
		{
			Sut->SetAnswerCombineRuleBinary(ESFCombineRuleBinary::Or);
		});
		Describe("with two true children", [this]
		{
			It("should yield a yes answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Yes());
			});
		});
		Describe("with one true, one false child", [this]
		{
			It("should yield a yes answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Yes());
			});
		});
		Describe("with two false children", [this]
		{
			It("should yield a no answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::No());
			});
		});
	});
	
	
	Describe("with fuzzy rule MEAN", [this]
	{
		BeforeEach([this]
		{
			Sut->SetAnswerCombineRuleFuzzy(ESFCombineRuleFuzzy::Mean);
		});
		Describe("with two true children", [this]
		{
			It("should yield a 1,0 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 1.0f);
			});
		});
		Describe("with one true, one false child", [this]
		{
			It("should yield a 0,5 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 0.5f);
			});
		});
		Describe("with two false children", [this]
		{
			It("should yield a 0,0 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 0.0f);
			});
		});
	});
	
	
	Describe("with fuzzy rule PERCENTILE", [this]
	{
		BeforeEach([this]
		{
			Sut->SetAnswerCombineRuleFuzzy(ESFCombineRuleFuzzy::Percentile);
		});
		Describe("with two true children", [this]
		{
			It("should yield a 1,0 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 1.0f);
			});
		});
		Describe("with one true, then one false child", [this]
		{
			It("should yield a 0,0 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 0.0f);
			});
		});
		Describe("with two false children", [this]
		{
			It("should yield a 0,0 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 0.0f);
			});
		});
		Describe("with five children and 0,36 at third position", [this]
		{
			It("should yield a 0,36 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				UMockSFConditional* MiddleConditional = NewObject<UMockSFConditional>();
				MiddleConditional->Answer = Answer::Create(true, 0.36f);
				Sut->TryAddChild(MiddleConditional);
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 0.36f);
			});
		});
	});
	Describe("with a child yielding a runtime error", [this]
	{
		It("should yield HasChildWithRuntimeError error state", [this]
		{
			Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
			auto* RuntimeErrorConditional = NewObject<UMockSFConditional>();
			RuntimeErrorConditional->Answer = Answer::Error::Mock();
			Sut->TryAddChild(RuntimeErrorConditional);
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Error::HasChildWithRuntimeError());
		});
	});
}

#endif WITH_AUTOMATION_WORKER