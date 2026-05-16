// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Utility/Conditional_Utility_AlwaysTrue.h"

SF::FConditionalAnswer SF::UConditional_Utility_AlwaysTrue::EvaluateInternal_Implementation(
	const FConditionalEvaluationContext& EvaluationContext)
{
	return Conditional::Answer::Yes();
}
