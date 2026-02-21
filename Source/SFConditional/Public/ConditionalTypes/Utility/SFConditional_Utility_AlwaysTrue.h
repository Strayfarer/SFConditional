// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditional.h"
#include "SFConditional_Utility_AlwaysTrue.generated.h"

/**
 * Conditional that always answers Yes.
 */
UCLASS(DisplayName="UTILITY - Always True")
class SFCONDITIONAL_API USFConditional_Utility_AlwaysTrue : public USFConditional
{
	GENERATED_BODY()
	
protected:
	// - USFConditional
	virtual FSFConditionalAnswer EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext) override;
	// --
};
