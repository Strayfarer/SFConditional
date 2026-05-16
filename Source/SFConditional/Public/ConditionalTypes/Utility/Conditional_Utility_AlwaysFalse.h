// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"
#include "Conditional_Utility_AlwaysFalse.generated.h"

namespace SF
{
	/**
	 * Conditional that always answers No.
	 */
	UCLASS(DisplayName="UTILITY - Always False")
	class SFCONDITIONAL_API UConditional_Utility_AlwaysFalse : public UConditional
	{
		GENERATED_BODY()

	protected:
		// UConditional
		virtual FConditionalAnswer EvaluateInternal_Implementation(
			const FConditionalEvaluationContext& EvaluationContext) override;
		// --
	};
}
