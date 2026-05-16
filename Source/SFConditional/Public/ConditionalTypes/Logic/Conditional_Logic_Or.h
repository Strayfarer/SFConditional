// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"
#include "Conditional_Logic_Or.generated.h"

namespace SF
{
	/**
	 * Answers Yes if *any* sub-conditional gives true as binary answer, otherwise No.
	 * 
	 * Note that the fuzzy answers of the sub-conditionals aren't considered in any way.
	 */
	UCLASS(DisplayName="LOGIC - Or")
	class SFCONDITIONAL_API UConditional_Logic_Or : public UConditional
	{
		GENERATED_BODY()

	protected:
		// UConditional
		virtual FConditionalAnswer EvaluateInternal_Implementation(
			const FConditionalEvaluationContext& EvaluationContext) override;
		virtual FInt32Range GetAllowedChildrenNumRange_Implementation() const override;
		virtual TArray<UConditional*> GetImmediateChildren_Implementation() const override;
		virtual FString CreateConfigurationDebugString_Implementation() const override;
#if WITH_EDITOR
		virtual bool TryAddChild_Implementation(UConditional* Child) override;
		virtual bool TryRemoveChild_Implementation(UConditional* Child) override;
#endif
		// --

		/** The conditionals to combine by OR. */
		UPROPERTY(EditDefaultsOnly, Instanced, meta=(TitleProperty=ConditionalTitlePropertyString))
		TArray<TObjectPtr<UConditional>> Conditions = {};
	};
}
