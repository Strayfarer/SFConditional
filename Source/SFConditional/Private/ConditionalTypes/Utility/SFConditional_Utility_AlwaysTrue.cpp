// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Utility/SFConditional_Utility_AlwaysTrue.h"

FSFConditionalAnswer USFConditional_Utility_AlwaysTrue::EvaluateInternal_Implementation(
	const FSFConditionalEvaluationContext& EvaluationContext)
{
	return SF::Conditional::Answer::Yes();
}
