// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Logic/Conditional_Logic_MultiCombine.h"

SF::FConditionalAnswer SF::UConditional_Logic_MultiCombine::EvaluateInternal_Implementation(const FConditionalEvaluationContext& EvaluationContext)
{
	bool bHadError = false;
	bool bBinaryAnswer = true;
	float FuzzyAnswer = 1.f;
	float AccumulatedFuzzyAnswer = 0.f;
	TArray<FConditionalAnswer> CollectedAnswers = {};
	
	for (UConditional* Condition : Conditions)
	{
		const FConditionalAnswer& Answer =
			CollectedAnswers.Add_GetRef(Condition->Evaluate(EvaluationContext));
		
		if (Answer.IsError())
		{
			bHadError = true;
			continue;
		}
		
		switch (AnswerCombineRuleBinary)
		{
			case ECombineRuleBinary::And: bBinaryAnswer &= Answer.GetBinaryAnswer(); break;
			case ECombineRuleBinary::Or:  bBinaryAnswer |= Answer.GetBinaryAnswer(); break;
		}
		AccumulatedFuzzyAnswer += Answer.GetFuzzyAnswer();
	}

	switch (AnswerCombineRuleFuzzy)
	{
		case ECombineRuleFuzzy::Mean:		  FuzzyAnswer = AccumulatedFuzzyAnswer / Conditions.Num(); break;
		case ECombineRuleFuzzy::Percentile: FuzzyAnswer = CollectedAnswers[Conditions.Num() / 2].GetFuzzyAnswer(); break;
	}

	return bHadError 
		? Conditional::Answer::Error::HasChildWithRuntimeError()
		: Conditional::Answer::Create(bBinaryAnswer, FuzzyAnswer);
}

FInt32Range SF::UConditional_Logic_MultiCombine::GetAllowedChildrenNumRange_Implementation() const
{
	return FInt32Range(TRangeBound<int>::Inclusive(2), FInt32RangeBound::Open());
}

TArray<SF::UConditional*> SF::UConditional_Logic_MultiCombine::GetImmediateChildren_Implementation() const
{
	TArray<UConditional*> Children = Super::GetImmediateChildren_Implementation();
	Children.Append(Conditions);
	return Children;
}

FString SF::UConditional_Logic_MultiCombine::CreateConfigurationDebugString_Implementation() const
{
	return FString(AnswerCombineRuleBinary == ECombineRuleBinary::And ? "And" : "Or") + ", "
		+ FString(AnswerCombineRuleFuzzy == ECombineRuleFuzzy::Mean ? "Mean" : "Percentile") + ", "
		+ FString::Printf(TEXT("%d sub-conditions"), Conditions.Num());
}

#if WITH_EDITOR
bool SF::UConditional_Logic_MultiCombine::TryAddChild_Implementation(UConditional* Child)
{
	Conditions.Emplace(Child);
	return true;
}

bool SF::UConditional_Logic_MultiCombine::TryRemoveChild_Implementation(UConditional* Child)
{
	return Conditions.Remove(Child) > 0;
}
#endif
