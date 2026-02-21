// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditional.h"
#include "SFConditional_Area_WorldDistanceRadius.generated.h"

/**
 * Returns whether the tested location is inside a sphere around the instigator.
* 
 * Notes:
 * - FuzzyScore returns 0.f if outside the radius, else closeness [0.f - 1.f] to instigator.
 * - Supports Actors, SceneComponents, ActorComponents (using owner transform).
 */
UCLASS(DisplayName="AREA - World Distance Radius")
class SFCONDITIONAL_API USFConditional_Area_WorldDistanceRadius : public USFConditional
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetRadius(const float InRadius) { Radius = InRadius; }
	
protected:
	// - USFConditional
	virtual FSFConditionalAnswer EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext) override;
	virtual FString CreateConfigurationDebugString_Implementation() const override;
#if WITH_GAMEPLAY_DEBUGGER
	virtual void VisualizeWithGameplayDebugger(FGameplayDebuggerCategory& Debugger, FGameplayDebuggerCanvasContext& Canvas) override;
#endif // WITH_GAMEPLAY_DEBUGGER
	// --

	/** Radius of the sphere around the instigator. */
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin=0, UIMin=0))
	float Radius = 50.f;
};
