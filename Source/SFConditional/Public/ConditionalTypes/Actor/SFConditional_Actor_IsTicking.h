// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditional.h"
#include "SFConditional_Actor_IsTicking.generated.h"

/**
 * Returns Yes if the tested object is an actor and ticks, No otherwise.
 */
UCLASS(DisplayName="ACTOR - Is Ticking")
class SFCONDITIONAL_API USFConditional_Actor_IsTicking : public USFConditional
{
	GENERATED_BODY()

protected:
	// - USFConditional
	virtual FSFConditionalAnswer EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext) override;
	// --
};
