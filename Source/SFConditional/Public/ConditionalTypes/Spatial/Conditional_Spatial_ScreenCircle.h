// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"

#include "Conditional_Spatial_ScreenCircle.generated.h"

namespace SF
{
	/**
	 * Returns whether the tested location is inside the specified screen circle
	 * of the player viewport.
	 * 
	 * Notes:
	 * - FuzzyScore returns 0.f if outside box, else closeness [0.f - 1.f] to screen center.
	 * - Supports Actors, SceneComponents, ActorComponents (using owner transform).
	 */
	UCLASS(DisplayName="SPATIAL - Screen Circle")
	class SFCONDITIONAL_API UConditional_Spatial_ScreenCircle : public UConditional
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

		UPROPERTY(EditDefaultsOnly)
		float Radius = 50.f;

		UPROPERTY(EditDefaultsOnly)
		float OffsetHorizontal = 0.f;

		UPROPERTY(EditDefaultsOnly)
		float OffsetVertical = 0.f;
	};
}
