// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditional.h"
#include "SFConditional_Object_IsOfClass.generated.h"

/**
 * Returns Yes if the tested object or a potential component owner is of the specified class, No otherwise.
 */
UCLASS(DisplayName="OBJECT - Is Of Class")
class SFCONDITIONAL_API USFConditional_Object_IsOfClass : public USFConditional
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetPreLoadedClassToCheckFor(const TSubclassOf<UObject>& InClass)
	{
		bPreloadClassToCheckFor = true;
		PreLoadedClassToCheckFor = InClass;
	}
	
	FORCEINLINE void SetSyncLoadedClassToCheckFor(const TSoftClassPtr<UObject>& InClass)
	{
		bPreloadClassToCheckFor = false;
		SyncLoadedClassToCheckFor = InClass;
	}
	
	FORCEINLINE void SetTryTestComponentOwner(const bool bInTryTestComponentOwner)
	{
		bTryTestAssociatedActor = bInTryTestComponentOwner;
	}

protected:
	// - UObject
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	// - USFConditional
	virtual FSFConditionalAnswer EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext) override;
	virtual FString CreateConfigurationDebugString_Implementation() const override;
	// --

	UClass* ResolveClassToCheckFor() const;
	
	/** 
	 * If set to true, the class will be preloaded and always kept in memory.
	 * If set to false, the class will be loaded on demand, leading to a hitch if it wasn't loaded by other means yet.
	 */
	UPROPERTY(EditDefaultsOnly)
	bool bPreloadClassToCheckFor = true;

	/** 
	 * The conditional returns true, if the tested object has this class. 
	 * Requires bPreloadClassToCheckFor = true.
	 */
	UPROPERTY(EditDefaultsOnly, meta=(EditCondition="bPreloadClassToCheckFor"))
	TSubclassOf<UObject> PreLoadedClassToCheckFor = nullptr;

	/**
	 * The conditional returns true, if the tested object has this class.
	 * Requires bPreloadClassToCheckFor = false.
	 */
	UPROPERTY(EditDefaultsOnly, meta=(EditCondition="!bPreloadClassToCheckFor"))
	TSoftClassPtr<UObject> SyncLoadedClassToCheckFor = nullptr;

	/** If true, the conditional will also check potential component owner actors for the class. */
	UPROPERTY(EditDefaultsOnly)
	bool bTryTestAssociatedActor = false;
};
