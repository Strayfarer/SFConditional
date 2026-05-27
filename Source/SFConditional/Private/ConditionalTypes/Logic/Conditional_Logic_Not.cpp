// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Logic/Conditional_Logic_Not.h"

SF::UConditional* SF::UConditional_Logic_Not::Instantiate(UObject* Outer, bool bIsRoot)
{
	auto* Instance = Cast<UConditional_Logic_Not>(Super::Instantiate(Outer, TODO));
	Instance->Condition = Condition->Instantiate(Outer, TODO);
	return Instance;
}

SF::FConditionalAnswer SF::UConditional_Logic_Not::EvaluateInternal_Implementation(const FConditionalEvaluationContext& EvaluationContext)
{
	const FConditionalAnswer Answer = Condition->Evaluate(EvaluationContext);
	return Answer.IsError()
		? Conditional::Answer::Error::HasChildWithRuntimeError()
		: Conditional::Answer::Create(!Answer.GetBinaryAnswer(), 1.f - Answer.GetFuzzyAnswer());
}

FInt32Range SF::UConditional_Logic_Not::GetAllowedChildrenNumRange_Implementation() const
{
	return FInt32Range(TRangeBound<int>::Inclusive(1), TRangeBound<int>::Inclusive(1));
}

TArray<SF::UConditional*> SF::UConditional_Logic_Not::GetImmediateChildren_Implementation() const
{
	TArray<UConditional*> Children = Super::GetImmediateChildren_Implementation();
	Children.Emplace(Condition);
	return Children;
}

FString SF::UConditional_Logic_Not::CreateConfigurationDebugString_Implementation() const
{
	if (!Condition)
	{
		return "";
	}
	
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
void SF::UConditional_Logic_Not::AddChild_Implementation(UConditional* Child)
{
	Condition = Child;
}

bool SF::UConditional_Logic_Not::TryRemoveChild_Implementation(UConditional* Child)
{
	if (Condition != Child)
	{
		return false;
	}
	Condition = nullptr;
	return true;
}
#endif
