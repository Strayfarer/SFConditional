// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Utility/Conditional_Utility_AlwaysFalse.h"

SF::FConditionalAnswer SF::UConditional_Utility_AlwaysFalse::EvaluateInternal_Implementation(
	const FConditionalEvaluationContext& EvaluationContext)
{
	return Conditional::Answer::No();
}
