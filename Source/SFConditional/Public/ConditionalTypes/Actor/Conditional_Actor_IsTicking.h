// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"
#include "Conditional_Actor_IsTicking.generated.h"

namespace SF
{
	/**
	 * Returns Yes if the tested object is an actor and ticks, No otherwise.
	 */
	UCLASS(DisplayName="ACTOR - Is Ticking")
	class SFCONDITIONAL_API UConditional_Actor_IsTicking : public UConditional
	{
		GENERATED_BODY()

	protected:
		// UConditional
		virtual FConditionalAnswer EvaluateInternal_Implementation(
			const FConditionalEvaluationContext& EvaluationContext) override;
		// --
	};
}
