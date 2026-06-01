// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"
#include "Conditional_Spatial_WorldSphere.generated.h"

namespace SF
{
	 /**
	 * Returns whether the tested location is inside a sphere around the instigator.
	 * 
	 * Notes:
	 * - FuzzyScore returns 0.f if outside the radius, else closeness [0.f - 1.f] to instigator.
	 * - Supports Actors, SceneComponents, ActorComponents (using owner transform).
	 */
	UCLASS(DisplayName="SPATIAL - World Sphere")
	class SFCONDITIONAL_API UConditional_Spatial_WorldSphere : public UConditional
	{
		GENERATED_BODY()

	public:
		FORCEINLINE void SetRadius(const float InRadius) { Radius = InRadius; }

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

		/** Radius of the sphere around the instigator. */
		UPROPERTY(EditDefaultsOnly, meta=(ClampMin=0, UIMin=0))
		float Radius = 50.f;
	};
}
