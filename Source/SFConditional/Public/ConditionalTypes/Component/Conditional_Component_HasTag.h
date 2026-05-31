// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"

#include "Conditional_Component_HasTag.generated.h"

namespace SF
{
	/**
	 * Returns Yes if the tested actor component has the configured tags, No otherwise.
	 */
	UCLASS(DisplayName="COMPONENT - Has Tag")
	class SFCONDITIONAL_API UConditional_Component_HasTag : public UConditional
	{
		GENERATED_BODY()

	public:
		FORCEINLINE void SetTags(const TSet<FName>& InTags)
		{
			Tags = InTags;
		}

	protected:
		// UObject
#if WITH_EDITOR
		virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
		// UConditional
		virtual FConditionalAnswer EvaluateInternal_Implementation(
			const FConditionalEvaluationContext& EvaluationContext) override;
		virtual FString CreateConfigurationDebugString_Implementation() const override;
		// --

		/** The conditional returns true, if the tested actor component has these tags. */
		UPROPERTY(EditDefaultsOnly)
		TSet<FName> Tags{};
	};
}
