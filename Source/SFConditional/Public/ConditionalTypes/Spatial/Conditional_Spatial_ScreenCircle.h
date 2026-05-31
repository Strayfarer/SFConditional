// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"

#include "Conditional_Spatial_ScreenCircle.generated.h"

namespace SF
{
	/**
	 * 
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
		virtual void VisualizeWithGameplayDebugger(FGameplayDebuggerCategory& Debugger,
												   FGameplayDebuggerCanvasContext& Canvas) override;
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
