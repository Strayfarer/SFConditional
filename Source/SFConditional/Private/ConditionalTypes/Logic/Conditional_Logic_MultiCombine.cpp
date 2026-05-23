// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Logic/Conditional_Logic_MultiCombine.h"

SF::FConditionalAnswer SF::UConditional_Logic_MultiCombine::EvaluateInternal_Implementation(const FConditionalEvaluationContext& EvaluationContext)
{
	bool bHadError = false;
	bool bBinaryAnswer = false;
	switch (AnswerCombineRuleBinary)
	{
		case ECombineRuleBinary::And: bBinaryAnswer = true; break;
		case ECombineRuleBinary::Or:  bBinaryAnswer = false; break;
	}
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

	float FuzzyAnswer = 0.f;
	switch (AnswerCombineRuleFuzzy)
	{
		case ECombineRuleFuzzy::Mean:
			FuzzyAnswer = AccumulatedFuzzyAnswer / Conditions.Num();
			break;
	case ECombineRuleFuzzy::Percentile:
			Algo::SortBy(CollectedAnswers, [](const FConditionalAnswer& Answer)
			{
				return Answer.GetFuzzyAnswer();
			});
			FuzzyAnswer = CollectedAnswers[Conditions.Num() / 2].GetFuzzyAnswer();
			break;
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
void SF::UConditional_Logic_MultiCombine::AddChild_Implementation(UConditional* Child)
{
	Conditions.Emplace(Child);
}

bool SF::UConditional_Logic_MultiCombine::TryRemoveChild_Implementation(UConditional* Child)
{
	return Conditions.Remove(Child) > 0;
}
#endif
