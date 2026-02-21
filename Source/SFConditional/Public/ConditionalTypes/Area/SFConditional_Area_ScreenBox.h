// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditional.h"
#include "SFConditional_Area_ScreenBox.generated.h"

/**
 * Returns whether the tested location is inside the specified screen box
 * of the player viewport.
 * 
 * Notes:
 * - FuzzyScore returns 0.f if outside box, else closeness [0.f - 1.f] to screen center.
 * - Supports Actors, SceneComponents, ActorComponents (using owner transform).
 */
UCLASS(DisplayName="AREA - Screen Box")
class SFCONDITIONAL_API USFConditional_Area_ScreenBox : public USFConditional
{
	GENERATED_BODY()

protected:
	// - USFConditional
	virtual FSFConditionalAnswer EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext) override;
	virtual FString CreateConfigurationDebugString_Implementation() const override;
#if WITH_GAMEPLAY_DEBUGGER
	virtual void VisualizeWithGameplayDebugger(FGameplayDebuggerCategory& Debugger, FGameplayDebuggerCanvasContext& Canvas) override;
#endif // WITH_GAMEPLAY_DEBUGGER
	// --

	/** Distance to top reference point (by default upper viewport border). */
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin=0, UIMin=0))
	float TopDistance = 50.f;

	/** Distance to right reference point (by default right viewport border). */
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin=0, UIMin=0))
	float RightDistance = 50.f;

	/** Distance to left reference point (by default left viewport border). */
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin=0, UIMin=0))
	float LeftDistance = 50.f;

	/** Distance to bottom reference point (by default bottom viewport border). */
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin=0, UIMin=0))
	float BottomDistance = 50.f;

	/**
	 * Whether to not take the viewport border as reference point for the distances,
	 * but the screen center.
	 * 
	 * If true, then e.g. TopDistance would be the distance from screen center to box
	 * border, instead of distance from top viewport border to box border.
	 */
	UPROPERTY(EditDefaultsOnly)
	bool bFromCenterInsteadOfBorder = false;
};
