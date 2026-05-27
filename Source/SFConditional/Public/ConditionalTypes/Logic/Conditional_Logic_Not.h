// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"
#include "Conditional_Logic_Not.generated.h"

namespace SF
{
	/**
	 * Answers Yes if the sub-conditional gives false as binary answer.
	 * Answers No if it answers true.
	 * Fuzzy answer is one minus the fuzzy answer of the sub-conditional.
	 */
	UCLASS(DisplayName="LOGIC - Not")
	class SFCONDITIONAL_API UConditional_Logic_Not : public UConditional
	{
		GENERATED_BODY()

	protected:
		// UConditional
		virtual UConditional* Instantiate(UObject* Outer, bool bIsRoot) override;
		virtual FConditionalAnswer EvaluateInternal_Implementation(
			const FConditionalEvaluationContext& EvaluationContext) override;
		virtual FInt32Range GetAllowedChildrenNumRange_Implementation() const override;
		virtual TArray<UConditional*> GetImmediateChildren_Implementation() const override;
		virtual FString CreateConfigurationDebugString_Implementation() const override;
#if WITH_EDITOR
		virtual void AddChild_Implementation(UConditional* Child) override;
		virtual bool TryRemoveChild_Implementation(UConditional* Child) override;
#endif
		// --

		/** The conditional to negate. */
		UPROPERTY(EditDefaultsOnly, Instanced, NoClear, meta=(NoResetToDefault, ForceShowPluginContent, TitleProperty=ConditionalTitlePropertyString))
		TObjectPtr<UConditional> Condition = nullptr;
	};
}
