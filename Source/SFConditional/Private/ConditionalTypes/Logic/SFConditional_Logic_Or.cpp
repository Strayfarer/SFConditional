// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Logic/SFConditional_Logic_Or.h"

FSFConditionalAnswer USFConditional_Logic_Or::EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext)
{
	bool bHadError = false;
	bool bBinaryAnswer = false;
	for (USFConditional* Predicate : Conditions)
	{
		const FSFConditionalAnswer Answer = Predicate->Evaluate(EvaluationContext);
		if (Answer.IsError())
		{
			bHadError = true;
			continue;
		}
		bBinaryAnswer |= Answer.GetBinaryAnswer();
	}
	return bHadError 
		? SF::Conditional::Answer::Error::HasChildWithRuntimeError()
		: SF::Conditional::Answer::FromBool(bBinaryAnswer);
}

FInt32Range USFConditional_Logic_Or::GetAllowedChildrenNumRange_Implementation() const
{
	return FInt32Range(TRangeBound<int>::Inclusive(2), FInt32RangeBound::Open());
}

TArray<USFConditional*> USFConditional_Logic_Or::GetImmediateChildren_Implementation() const
{
	TArray<USFConditional*> Children = Super::GetImmediateChildren_Implementation();
	Children.Append(Conditions);
	return Children;
}

FString USFConditional_Logic_Or::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT("%d sub-conditions"), Conditions.Num());
}

#if WITH_EDITOR
bool USFConditional_Logic_Or::TryAddChild_Implementation(USFConditional* Child)
{
	Conditions.Emplace(Child);
	return true;
}

bool USFConditional_Logic_Or::TryRemoveChild_Implementation(USFConditional* Child)
{
	return Conditions.Remove(Child) > 0;
}
#endif
