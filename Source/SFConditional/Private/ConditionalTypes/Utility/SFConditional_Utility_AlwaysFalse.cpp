// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Utility/SFConditional_Utility_AlwaysFalse.h"

FSFConditionalAnswer USFConditional_Utility_AlwaysFalse::EvaluateInternal_Implementation(
	const FSFConditionalEvaluationContext& EvaluationContext)
{
	return SF::Conditional::Answer::No();
}
