// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"
#include "Conditional_Logic_MultiCombine.generated.h"

namespace SF
{
	UENUM()
	enum class ECombineRuleBinary : uint8
	{
		/** Give binary answer true, only if *all* conditionals give binary answer true. */
		And,

		/** Give binary answer true, if *any* conditional gives binary answer true. */
		Or
	};

	UENUM()
	enum class ECombineRuleFuzzy : uint8
	{
		/** Sum all fuzzy answers and divide them by the number of answers. */
		Mean,

		/** 
		 * Sort all fuzzy answers and return the one in the middle. 
		 * Choose the higher-placed answer if the number of answers is even.
		 */
		Percentile
	};

	/**
	 * Combines an array of sub-conditional answers via user-defined rules for both the binary and fuzzy answer.
	 */
	UCLASS(DisplayName="LOGIC - Multi Combine")
	class SFCONDITIONAL_API UConditional_Logic_MultiCombine : public UConditional
	{
		GENERATED_BODY()

	public:
		FORCEINLINE void SetAnswerCombineRuleBinary(const ECombineRuleBinary& NewRule)
		{
			AnswerCombineRuleBinary = NewRule;
		}

		FORCEINLINE void SetAnswerCombineRuleFuzzy(const ECombineRuleFuzzy& NewRule)
		{
			AnswerCombineRuleFuzzy = NewRule;
		}

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

		/** The conditionals to combine. */
		UPROPERTY(EditDefaultsOnly, Instanced, meta=(TitleProperty=ConditionalTitlePropertyString))
		TArray<TObjectPtr<UConditional>> Conditions = {};

		/** Determines how the binary answers are combined. */
		UPROPERTY(EditDefaultsOnly, DisplayName="AnswerCombineRule - Binary")
		ECombineRuleBinary AnswerCombineRuleBinary = ECombineRuleBinary::And;

		/** Determines how the fuzzy answers are combined. */
		UPROPERTY(EditDefaultsOnly, DisplayName="AnswerCombineRule - Fuzzy")
		ECombineRuleFuzzy AnswerCombineRuleFuzzy = ECombineRuleFuzzy::Mean;
	};
}
