// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"
#include "Conditional_Utility_AlwaysTrue.generated.h"

namespace SF
{
	/**
	 * Conditional that always answers Yes.
	 */
	UCLASS(DisplayName="UTILITY - Always True")
	class SFCONDITIONAL_API UConditional_Utility_AlwaysTrue : public UConditional
	{
		GENERATED_BODY()

	protected:
		// UConditional
		virtual FConditionalAnswer EvaluateInternal_Implementation(
			const FConditionalEvaluationContext& EvaluationContext) override;
		// --
	};
}
