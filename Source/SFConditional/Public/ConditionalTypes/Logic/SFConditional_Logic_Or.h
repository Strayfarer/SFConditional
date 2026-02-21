// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditional.h"
#include "SFConditional_Logic_Or.generated.h"

/**
 * Answers Yes if *any* sub-conditional gives true as binary answer, otherwise No.
 * 
 * Note that the fuzzy answers of the sub-conditionals aren't considered in any way.
 */
UCLASS(DisplayName="LOGIC - Or")
class SFCONDITIONAL_API USFConditional_Logic_Or : public USFConditional
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

	/** The conditionals to combine by OR. */
	UPROPERTY(EditDefaultsOnly, Instanced, meta=(TitleProperty=ConditionalTitlePropertyString))
	TArray<TObjectPtr<USFConditional>> Conditions = {};
};
