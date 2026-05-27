// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Logic/Conditional_Logic_Or.h"

SF::UConditional* SF::UConditional_Logic_Or::Instantiate(UObject* Outer, bool bIsRoot)
{
	auto* Instance = Cast<UConditional_Logic_Or>(Super::Instantiate(Outer, TODO));
	
	TArray<UConditional*> InstantiatedChildren{};
	for (UConditional* Child : Conditions)
	{
		InstantiatedChildren.Emplace(Child->Instantiate(Outer, TODO));
	}
	
	Instance->Conditions = InstantiatedChildren;
	return Instance;
}

SF::FConditionalAnswer SF::UConditional_Logic_Or::EvaluateInternal_Implementation(const FConditionalEvaluationContext& EvaluationContext)
{
	bool bHadError = false;
	bool bBinaryAnswer = false;
	for (UConditional* Predicate : Conditions)
	{
		const FConditionalAnswer Answer = Predicate->Evaluate(EvaluationContext);
		if (Answer.IsError())
		{
			bHadError = true;
			continue;
		}
		bBinaryAnswer |= Answer.GetBinaryAnswer();
	}
	return bHadError 
		? Conditional::Answer::Error::HasChildWithRuntimeError()
		: Conditional::Answer::FromBool(bBinaryAnswer);
}

FInt32Range SF::UConditional_Logic_Or::GetAllowedChildrenNumRange_Implementation() const
{
	return FInt32Range(TRangeBound<int>::Inclusive(2), FInt32RangeBound::Open());
}

TArray<SF::UConditional*> SF::UConditional_Logic_Or::GetImmediateChildren_Implementation() const
{
	TArray<UConditional*> Children = Super::GetImmediateChildren_Implementation();
	Children.Append(Conditions);
	return Children;
}

FString SF::UConditional_Logic_Or::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT("%d sub-conditions"), Conditions.Num());
}

#if WITH_EDITOR
void SF::UConditional_Logic_Or::AddChild_Implementation(UConditional* Child)
{
	Conditions.Emplace(Child);
}

bool SF::UConditional_Logic_Or::TryRemoveChild_Implementation(UConditional* Child)
{
	return Conditions.Remove(Child) > 0;
}
#endif
