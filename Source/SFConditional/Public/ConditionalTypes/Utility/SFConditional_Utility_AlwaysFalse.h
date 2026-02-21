// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditional.h"
#include "SFConditional_Utility_AlwaysFalse.generated.h"

/**
 * Conditional that always answers No.
 */
UCLASS(DisplayName="UTILITY - Always False")
class SFCONDITIONAL_API USFConditional_Utility_AlwaysFalse : public USFConditional
{
	GENERATED_BODY()
	
protected:
	// - USFConditional
	virtual FSFConditionalAnswer EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext) override;
	// --
};
