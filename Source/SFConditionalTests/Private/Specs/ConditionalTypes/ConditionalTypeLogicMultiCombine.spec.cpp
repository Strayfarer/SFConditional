// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "ConditionalTypes/Logic/Conditional_Logic_MultiCombine.h"
#include "ConditionalTypes/Utility/Conditional_Utility_AlwaysFalse.h"
#include "ConditionalTypes/Utility/Conditional_Utility_AlwaysTrue.h"
#include "Misc/AutomationTest.h"
#include "Mocks/Conditional_MockObject.h"
#include "Mocks/Conditional_MockConditional.h"

using namespace SF::Conditional;

BEGIN_DEFINE_SPEC(FConditionalTypeLogicMultiCombineSpec, "SF.Conditional.Types.Logic.MultiCombine", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TObjectPtr<SF::UConditional_Logic_MultiCombine> Sut = nullptr;
	TObjectPtr<UObject> Object = nullptr;
END_DEFINE_SPEC(FConditionalTypeLogicMultiCombineSpec)

void FConditionalTypeLogicMultiCombineSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<SF::UConditional_Logic_MultiCombine>();
		Object = NewObject<UConditional_MockObject>();
	});
	
	Describe("with binary rule AND", [this]
	{
		BeforeEach([this]
		{
			Sut->SetAnswerCombineRuleBinary(SF::ECombineRuleBinary::And);
		});
		Describe("with two true children", [this]
		{
			It("should yield a yes answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Yes());
			});
		});
		Describe("with one true, one false child", [this]
		{
			It("should yield a [false, 0,5] answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Create(false, 0.5f));
			});
		});
		Describe("with two false children", [this]
		{
			It("should yield a no answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysFalse>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::No());
			});
		});
	});
	
	
	Describe("with binary rule OR", [this]
	{
		BeforeEach([this]
		{
			Sut->SetAnswerCombineRuleBinary(SF::ECombineRuleBinary::Or);
		});
		Describe("with two true children", [this]
		{
			It("should yield a yes answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Yes());
			});
		});
		Describe("with one true, one false child", [this]
		{
			It("should yield a [true, 0,5] answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Create(true, 0.5f));
			});
		});
		Describe("with two false children", [this]
		{
			It("should yield a no answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysFalse>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::No());
			});
		});
	});
	
	
	Describe("with fuzzy rule MEAN", [this]
	{
		BeforeEach([this]
		{
			Sut->SetAnswerCombineRuleFuzzy(SF::ECombineRuleFuzzy::Mean);
		});
		Describe("with two true children", [this]
		{
			It("should yield a 1,0 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				TestEqual("Conditional Fuzzy Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 1.0f);
			});
		});
		Describe("with one true, one false child", [this]
		{
			It("should yield a 0,5 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Fuzzy Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 0.5f);
			});
		});
		Describe("with two false children", [this]
		{
			It("should yield a 0,0 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysFalse>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Fuzzy Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 0.0f);
			});
		});
	});
	
	
	Describe("with fuzzy rule PERCENTILE", [this]
	{
		BeforeEach([this]
		{
			Sut->SetAnswerCombineRuleFuzzy(SF::ECombineRuleFuzzy::Percentile);
		});
		Describe("with two true children", [this]
		{
			It("should yield a 1,0 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				TestEqual("Conditional Fuzzy Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 1.0f);
			});
		});
		Describe("with one true, then one false child", [this]
		{
			It("should yield a 0,0 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Fuzzy Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 1.0f);
			});
		});
		Describe("with two false children", [this]
		{
			It("should yield a 0,0 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysFalse>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysFalse>());
				TestEqual("Conditional Fuzzy Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 0.0f);
			});
		});
		Describe("with children [ AlwaysTrue, AlwaysTrue, 0,36, AlwaysTrue, AlwaysTrue ]", [this]
		{
			It("should yield a 1,0 fuzzy answer", [this]
			{
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				auto* MiddleConditional = NewObject<UConditional_MockConditional>();
				MiddleConditional->Answer = Answer::Create(true, 0.36f);
				Sut->TryAddChild(MiddleConditional);
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
				TestEqual("Conditional Fuzzy Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 1.f);
			});
		});
		Describe("with children [ 0,1 | 0,3 | 0,2 | 0,9 | 0,8 ] and mixed binary answers", [this]
		{
			It("should yield a 0,3 fuzzy answer", [this]
			{
				auto* Conditional1 = NewObject<UConditional_MockConditional>();
				Conditional1->Answer = Answer::Create(true, 0.1f);
				Sut->TryAddChild(Conditional1);
				
				auto* Conditional3 = NewObject<UConditional_MockConditional>();
				Conditional3->Answer = Answer::Create(true, 0.3f);
				Sut->TryAddChild(Conditional3);
				
				auto* Conditional2 = NewObject<UConditional_MockConditional>();
				Conditional2->Answer = Answer::Create(false, 0.2f);
				Sut->TryAddChild(Conditional2);
				
				auto* Conditional5 = NewObject<UConditional_MockConditional>();
				Conditional5->Answer = Answer::Create(false, 0.9f);
				Sut->TryAddChild(Conditional5);
				
				auto* Conditional4 = NewObject<UConditional_MockConditional>();
				Conditional4->Answer = Answer::Create(true, 0.8f);
				Sut->TryAddChild(Conditional4);
				
				TestEqual("Conditional Fuzzy Answer", Sut->EvaluateObject(Object).GetFuzzyAnswer(), 0.3f);
			});
		});
	});
	Describe("with a child yielding a runtime error", [this]
	{
		It("should yield HasChildWithRuntimeError error state", [this]
		{
			Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
			auto* RuntimeErrorConditional = NewObject<UConditional_MockConditional>();
			RuntimeErrorConditional->Answer = Answer::Error::MockA();
			Sut->TryAddChild(RuntimeErrorConditional);
			Sut->TryAddChild(NewObject<SF::UConditional_Utility_AlwaysTrue>());
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Error::HasChildWithRuntimeError());
		});
	});
}

#endif WITH_AUTOMATION_WORKER