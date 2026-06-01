// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"

#include "Conditional_Spatial_LineOfSight.generated.h"

namespace SF
{
	/**
	* Returns whether the tested location is hit by line traces starting from the instigator.
	* 
	* Notes:
	* - FuzzyScore returns 0.f if outside the trace distance, else closeness [0.f - 1.f] to instigator.
	*/
	UCLASS(DisplayName="SPATIAL - Line of Sight")
	class SFCONDITIONAL_API UConditional_Spatial_LineOfSight : public UConditional
	{
		GENERATED_BODY()

	protected:
		// UConditional
		virtual FConditionalAnswer EvaluateInternal_Implementation(
			const FConditionalEvaluationContext& EvaluationContext) override;
		virtual FString CreateConfigurationDebugString_Implementation() const override;
#if WITH_GAMEPLAY_DEBUGGER
		virtual void VisualizeWithGameplayDebugger(
			const FConditionalEvaluationContext& EvaluationContext, FGameplayDebuggerCategory& Debugger, FGameplayDebuggerCanvasContext& Canvas) override;
#endif // WITH_GAMEPLAY_DEBUGGER
		// --
	};

	namespace Conditional::Answer::Error
	{
		SFCONDITIONAL_API const FConditionalAnswer& NoLineOfSightComponentAvailable();
	}
}
