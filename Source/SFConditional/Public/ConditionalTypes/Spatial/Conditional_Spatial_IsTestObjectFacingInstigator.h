// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"

#include "Conditional_Spatial_IsTestObjectFacingInstigator.generated.h"

namespace SF
{
	/**
	* Returns whether the test object is facing the instigator.
	* 
	* Notes:
	* - FuzzyScore returns 0.f if outside the max angle, else closeness [0.f - 1.f] to the optimal angle (facing straight).
	* - Supports Actors, SceneComponents, ActorComponents (using owner transform).
	*/
	UCLASS(DisplayName="SPATIAL - Is Test Object Facing Instigator")
	class SFCONDITIONAL_API UConditional_Spatial_IsTestObjectFacingInstigator : public UConditional
	{
		GENERATED_BODY()

	protected:
		// UConditional
		virtual FConditionalAnswer EvaluateInternal_Implementation(
			const FConditionalEvaluationContext& EvaluationContext) override;
		virtual FString CreateConfigurationDebugString_Implementation() const override;
#if WITH_GAMEPLAY_DEBUGGER
		virtual void VisualizeTestObjectWithGameplayDebugger(const FConditionalEvaluationContext& EvaluationContext,
												   FGameplayDebuggerCategory& Debugger, FGameplayDebuggerCanvasContext& Canvas) override;
#endif // WITH_GAMEPLAY_DEBUGGER
		// --

		UPROPERTY(EditDefaultsOnly, meta=(Units="deg"))
		float MaxAngle = 30.f;
	};
}
