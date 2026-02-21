// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Logic/SFConditional_Logic_And.h"

#include "SFConditionalDebugTrace.h"

FSFConditionalAnswer USFConditional_Logic_And::EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext)
{
	bool bBinaryAnswer = true;
	for (USFConditional* Predicate : Conditions)
	{
		bBinaryAnswer &= Predicate->Evaluate(EvaluationContext).GetBinaryAnswer();
	}
	return SF::Conditional::Answer::FromBool(bBinaryAnswer);
}

FInt32Range USFConditional_Logic_And::GetAllowedChildrenNumRange_Implementation() const
{
	return FInt32Range(TRangeBound<int>::Inclusive(2), FInt32RangeBound::Open());
}

TArray<USFConditional*> USFConditional_Logic_And::GetImmediateChildren_Implementation() const
{
	TArray<USFConditional*> Children = Super::GetImmediateChildren_Implementation();
	Children.Append(Conditions);
	return Children;
}

FString USFConditional_Logic_And::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT("%d sub-conditions"), Conditions.Num());
}

#if WITH_EDITOR
bool USFConditional_Logic_And::TryAddChild_Implementation(USFConditional* Child)
{
	Conditions.Emplace(Child);
	return true;
}

bool USFConditional_Logic_And::TryRemoveChild_Implementation(USFConditional* Child)
{
	return Conditions.Remove(Child) > 0;
}
#endif
