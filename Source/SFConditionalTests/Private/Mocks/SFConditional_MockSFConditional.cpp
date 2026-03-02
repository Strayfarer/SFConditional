// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "SFConditional_MockSFConditional.h"

#if WITH_EDITOR
bool USFConditional_MockSFConditional::TryAddChild_Implementation(USFConditional* Child)
{
	Children.Emplace(Child);
	return true;
}

bool USFConditional_MockSFConditional::TryRemoveChild_Implementation(USFConditional* Child)
{
	return Children.Remove(Child) > 0;
}
#endif

FSFConditionalAnswer USFConditional_MockSFConditional::EvaluateInternal_Implementation(
	const FSFConditionalEvaluationContext& EvaluationContext)
{
	return Answer;
}

FInt32Range USFConditional_MockSFConditional::GetAllowedChildrenNumRange_Implementation() const
{
	return AllowedChildrenNumRange;
}

TArray<USFConditional*> USFConditional_MockSFConditional::GetImmediateChildren_Implementation() const
{
	return Children;
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::Mock()
{
	static FSFConditionalAnswer Instance = FromErrorMsg(FName("Mock"));
	return Instance;
}
