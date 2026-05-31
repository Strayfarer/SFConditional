// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Conditional.h"

#include "Conditional_Actor_HasTag.generated.h"

namespace SF
{
	/**
	 * Returns Yes if the tested object is an actor and has the configured component, No otherwise.
	 */
	UCLASS(DisplayName="ACTOR - Has Tag")
	class SFCONDITIONAL_API UConditional_Actor_HasTag : public UConditional
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

		/** The conditional returns true, if the tested actor has these tags. */
		UPROPERTY(EditDefaultsOnly)
		TSet<FName> Tags{};
	};
}
