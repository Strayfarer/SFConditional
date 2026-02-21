// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditional.h"
#include "SFConditional_Actor_HasComponent.generated.h"

/**
 * Returns Yes if the tested object is an actor and has the configured component, No otherwise.
 */
UCLASS(DisplayName="ACTOR - Has Component")
class SFCONDITIONAL_API USFConditional_Actor_HasComponent : public USFConditional
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetComponentClass(const TSubclassOf<UActorComponent>& InComponentClass)
	{
		ComponentClass = InComponentClass;
	}
	
protected:
	// - UObject
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
	// - USFConditional
	virtual FSFConditionalAnswer EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext) override;
	virtual FString CreateConfigurationDebugString_Implementation() const override;
	// --
	
	/** The conditional returns true, if the tested object has this component. */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UActorComponent> ComponentClass = nullptr;
};
