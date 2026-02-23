// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Logic/SFConditional_Logic_Not.h"

FSFConditionalAnswer USFConditional_Logic_Not::EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext)
{
	const FSFConditionalAnswer Answer = Condition->Evaluate(EvaluationContext);
	return Answer.IsError()
		? SF::Conditional::Answer::Error::HasChildWithRuntimeError()
		: SF::Conditional::Answer::Create(!Answer.GetBinaryAnswer(), 1.f - Answer.GetFuzzyAnswer());
}

FInt32Range USFConditional_Logic_Not::GetAllowedChildrenNumRange_Implementation() const
{
	return FInt32Range(TRangeBound<int>::Inclusive(1), TRangeBound<int>::Inclusive(1));
}

TArray<USFConditional*> USFConditional_Logic_Not::GetImmediateChildren_Implementation() const
{
	TArray<USFConditional*> Children = Super::GetImmediateChildren_Implementation();
	Children.Emplace(Condition);
	return Children;
}

FString USFConditional_Logic_Not::CreateConfigurationDebugString_Implementation() const
{
	const FString ConditionNameFull = Condition.GetName();
	
	FString ConditionNameWithoutIndex;
	FString DiscardedIndex;
	ConditionNameFull.Split("_", &ConditionNameWithoutIndex, &DiscardedIndex, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	
	FString DiscardedPrefix;
	FString ConditionName;
	ConditionNameWithoutIndex.Split("_", &DiscardedPrefix, &ConditionName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);

	return "!" + ConditionName;
}

#if WITH_EDITOR
bool USFConditional_Logic_Not::TryAddChild_Implementation(USFConditional* Child)
{
	if (Condition)
	{
		return false;
	}
	Condition = Child;
	return true;
}

bool USFConditional_Logic_Not::TryRemoveChild_Implementation(USFConditional* Child)
{
	if (Condition != Child)
	{
		return false;
	}
	Condition = nullptr;
	return true;
}
#endif
