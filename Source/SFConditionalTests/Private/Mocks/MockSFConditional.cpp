// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "MockSFConditional.h"

#if WITH_EDITOR
bool UMockSFConditional::TryAddChild_Implementation(USFConditional* Child)
{
	Children.Emplace(Child);
	return true;
}

bool UMockSFConditional::TryRemoveChild_Implementation(USFConditional* Child)
{
	return Children.Remove(Child) > 0;
}
#endif

FSFConditionalAnswer UMockSFConditional::EvaluateInternal_Implementation(
	const FSFConditionalEvaluationContext& EvaluationContext)
{
	return Answer;
}

FInt32Range UMockSFConditional::GetAllowedChildrenNumRange_Implementation() const
{
	return AllowedChildrenNumRange;
}

TArray<USFConditional*> UMockSFConditional::GetImmediateChildren_Implementation() const
{
	return Children;
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::Mock()
{
	static FSFConditionalAnswer Instance = FromErrorMsg(FName("Mock"));
	return Instance;
}
