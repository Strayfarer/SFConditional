// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditional.h"
#include "SFConditional_Logic_Not.generated.h"

/**
 * Answers Yes if the sub-conditional gives false as binary answer.
 * Answers No if it answers true.
 * Fuzzy answer is one minus the fuzzy answer of the sub-conditional.
 */
UCLASS(DisplayName="LOGIC - Not")
class SFCONDITIONAL_API USFConditional_Logic_Not : public USFConditional
{
	GENERATED_BODY()

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

	/** The conditional to negate. */
	UPROPERTY(EditDefaultsOnly, Instanced, meta=(TitleProperty=ConditionalTitlePropertyString))
	TObjectPtr<USFConditional> Condition = nullptr;
};
