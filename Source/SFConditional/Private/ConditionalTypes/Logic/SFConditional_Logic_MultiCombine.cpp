// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Logic/SFConditional_Logic_MultiCombine.h"

FSFConditionalAnswer USFConditional_Logic_MultiCombine::EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext)
{
	bool bHadError = false;
	bool bBinaryAnswer = true;
	float FuzzyAnswer = 1.f;
	float AccumulatedFuzzyAnswer = 0.f;
	TArray<FSFConditionalAnswer> CollectedAnswers = {};
	
	for (USFConditional* Condition : Conditions)
	{
		const FSFConditionalAnswer& Answer =
			CollectedAnswers.Add_GetRef(Condition->Evaluate(EvaluationContext));
		
		if (Answer.IsError())
		{
			bHadError = true;
			continue;
		}
		
		switch (AnswerCombineRuleBinary)
		{
			case ESFCombineRuleBinary::And: bBinaryAnswer &= Answer.GetBinaryAnswer(); break;
			case ESFCombineRuleBinary::Or:  bBinaryAnswer |= Answer.GetBinaryAnswer(); break;
		}
		AccumulatedFuzzyAnswer += Answer.GetFuzzyAnswer();
	}

	switch (AnswerCombineRuleFuzzy)
	{
		case ESFCombineRuleFuzzy::Mean:		  FuzzyAnswer = AccumulatedFuzzyAnswer / Conditions.Num(); break;
		case ESFCombineRuleFuzzy::Percentile: FuzzyAnswer = CollectedAnswers[Conditions.Num() / 2].GetFuzzyAnswer(); break;
	}

	return bHadError 
		? SF::Conditional::Answer::Error::HasChildWithRuntimeError()
		: SF::Conditional::Answer::Create(bBinaryAnswer, FuzzyAnswer);
}

FInt32Range USFConditional_Logic_MultiCombine::GetAllowedChildrenNumRange_Implementation() const
{
	return FInt32Range(TRangeBound<int>::Inclusive(2), FInt32RangeBound::Open());
}

TArray<USFConditional*> USFConditional_Logic_MultiCombine::GetImmediateChildren_Implementation() const
{
	TArray<USFConditional*> Children = Super::GetImmediateChildren_Implementation();
	Children.Append(Conditions);
	return Children;
}

FString USFConditional_Logic_MultiCombine::CreateConfigurationDebugString_Implementation() const
{
	return FString(AnswerCombineRuleBinary == ESFCombineRuleBinary::And ? "And" : "Or") + ", "
		+ FString(AnswerCombineRuleFuzzy == ESFCombineRuleFuzzy::Mean ? "Mean" : "Percentile") + ", "
		+ FString::Printf(TEXT("%d sub-conditions"), Conditions.Num());
}

#if WITH_EDITOR
bool USFConditional_Logic_MultiCombine::TryAddChild_Implementation(USFConditional* Child)
{
	Conditions.Emplace(Child);
	return true;
}

bool USFConditional_Logic_MultiCombine::TryRemoveChild_Implementation(USFConditional* Child)
{
	return Conditions.Remove(Child) > 0;
}
#endif
