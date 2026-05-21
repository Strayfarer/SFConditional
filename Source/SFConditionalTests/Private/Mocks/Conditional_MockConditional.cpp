// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "Conditional_MockConditional.h"

#if WITH_EDITOR
bool UConditional_MockConditional::TryAddChild_Implementation(UConditional* Child)
{
	Children.Emplace(Child);
	return true;
}

bool UConditional_MockConditional::TryRemoveChild_Implementation(UConditional* Child)
{
	return Children.Remove(Child) > 0;
}
#endif

SF::FConditionalAnswer UConditional_MockConditional::EvaluateInternal_Implementation(
	const SF::FConditionalEvaluationContext& EvaluationContext)
{
	return Answer;
}

FInt32Range UConditional_MockConditional::GetAllowedChildrenNumRange_Implementation() const
{
	return AllowedChildrenNumRange;
}

TArray<SF::UConditional*> UConditional_MockConditional::GetImmediateChildren_Implementation() const
{
	return Children;
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::MockA()
{
	static FConditionalAnswer Instance = FromErrorMsg(FName("MockA"));
	return Instance;
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::MockB()
{
	static FConditionalAnswer Instance = FromErrorMsg(FName("MockB"));
	return Instance;
}
