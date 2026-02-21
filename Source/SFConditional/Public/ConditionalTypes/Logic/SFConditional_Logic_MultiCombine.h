// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditional.h"
#include "SFConditional_Logic_MultiCombine.generated.h"

UENUM() enum class ESFCombineRuleBinary : uint8
{
	/** Give binary answer true, only if *all* conditionals give binary answer true. */
	And,
	
	/** Give binary answer true, if *any* conditional gives binary answer true. */
	Or
};

UENUM() enum class ESFCombineRuleFuzzy : uint8
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
class SFCONDITIONAL_API USFConditional_Logic_MultiCombine : public USFConditional
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetAnswerCombineRuleBinary(const ESFCombineRuleBinary& NewRule) { AnswerCombineRuleBinary = NewRule; }
	FORCEINLINE void SetAnswerCombineRuleFuzzy(const ESFCombineRuleFuzzy& NewRule) { AnswerCombineRuleFuzzy = NewRule; }
	
protected:
	// - USFConditional
	virtual FSFConditionalAnswer EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext) override;
	virtual FInt32Range GetAllowedChildrenNumRange_Implementation() const override;
	virtual TArray<USFConditional*> GetImmediateChildren_Implementation() const override;
	virtual FString CreateConfigurationDebugString_Implementation() const override;
#if WITH_EDITOR
	virtual bool TryAddChild_Implementation(USFConditional* Child) override;
	virtual bool TryRemoveChild_Implementation(USFConditional* Child) override;
#endif
	// --
	
	/** The conditionals to combine. */
	UPROPERTY(EditDefaultsOnly, Instanced, meta=(TitleProperty=ConditionalTitlePropertyString))
	TArray<TObjectPtr<USFConditional>> Conditions = {};

	/** Determines how the binary answers are combined. */
	UPROPERTY(EditDefaultsOnly, DisplayName="AnswerCombineRule - Binary")
	ESFCombineRuleBinary AnswerCombineRuleBinary = ESFCombineRuleBinary::And;

	/** Determines how the fuzzy answers are combined. */
	UPROPERTY(EditDefaultsOnly, DisplayName="AnswerCombineRule - Fuzzy")
	ESFCombineRuleFuzzy AnswerCombineRuleFuzzy = ESFCombineRuleFuzzy::Mean;
};
