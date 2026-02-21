// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditionalAnswer.h"
#include "SFConditionalEvaluationContext.h"
#if WITH_GAMEPLAY_DEBUGGER
#include "GameplayDebuggerCategory.h"
#endif // WITH_GAMEPLAY_DEBUGGER
#include "UObject/Object.h"
#include "SFConditional.generated.h"

/**
 * A conditional is a question by some instigator UObject about another UObject (e.g. a component or actor), 
 * yielding both a binary (true/false) and fuzzy answer (0.f - 1.f).
 * 
 * Conditionals can have children and thus form complex expressions.
 *
 * Dev note: when using conditional object pointer properties in containers, you can add
 * TitleProperty=ConditionalTitlePropertyString as meta attribute, to get a nice title string
 * per container entry.
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class SFCONDITIONAL_API USFConditional : public UObject
{
	GENERATED_BODY()

public:
	// - UObject
	virtual void Serialize(FArchive& Ar) override;
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	// --
	
	/**
	 * Evaluate this conditional for an object.
	 * 
	 * @param TestObject The object to test.
	 * @return A binary and fuzzy answer.
	 */
	UFUNCTION(BlueprintCallable, Category="Conditional")
	FSFConditionalAnswer EvaluateObject(UObject* TestObject);
	
	/**
	 * Evaluate this conditional for an instigator on an object, as set in the evaluation context.
	 * Fills the context's debug trace (if set) with debug information.
	 * 
	 * @param EvaluationContext The parameters for this evaluation, most notably the object to test.
	 * @return A binary and fuzzy answer.
	 */
	UFUNCTION(BlueprintCallable, Category="Conditional")
	FSFConditionalAnswer Evaluate(const FSFConditionalEvaluationContext& EvaluationContext);
	
	FORCEINLINE float GetWeight() const { return Weight; }
	FORCEINLINE bool IsOptional() const { return bIsOptional; }
	FORCEINLINE bool IsInverted() const { return bIsInverted; }
	FORCEINLINE bool DoesImpactScoreOnFail() const { return bDoesImpactScoreOnFail; }

	void ForThisAndEachChildDo(const TFunction<void(USFConditional*)>& Work);

	/** Returns any immediate conditional children. */
	UFUNCTION(BlueprintNativeEvent, Category="Conditional")
	TArray<USFConditional*> GetImmediateChildren() const;
	
	/** Returns how many conditional children this is allowed to have. */
	UFUNCTION(BlueprintNativeEvent, Category="Conditional")
	FInt32Range GetAllowedChildrenNumRange() const;

	/** Generate a debug string containing information about the configuration of the specific conditional. */
	UFUNCTION(BlueprintNativeEvent, Category="Conditional")
	FString CreateConfigurationDebugString() const;

#if WITH_GAMEPLAY_DEBUGGER
	/** Generate a visualization of this conditional for the gameplay debugger. */
	virtual void VisualizeWithGameplayDebugger(FGameplayDebuggerCategory& Debugger, FGameplayDebuggerCanvasContext& Canvas);
#endif // WITH_GAMEPLAY_DEBUGGER
	
#if WITH_EDITOR
	UFUNCTION(BlueprintNativeEvent, Category="Conditional")
	bool TryAddChild(USFConditional* Child);
	
	UFUNCTION(BlueprintNativeEvent, Category="Conditional")
	bool TryRemoveChild(USFConditional* Child);
#endif
	
protected:
	/**
	 * Run the bare custom evaluation logic per conditional, without important post-processing steps.
	 * Should never be called by any other method than USFConditional::Evaluate(..).
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Conditional")
	FSFConditionalAnswer EvaluateInternal(UPARAM(ref) const FSFConditionalEvaluationContext& EvaluationContext);
	
#if WITH_EDITOR
	FString GetPathNamePrettified() const;
#endif
	
	/** 
	 * The weight will be multiplied with the fuzzy answer after the conditional has been evaluated.
	 * This is modification No. 1 after the internal evaluation has been done.
	 */
	UPROPERTY(EditDefaultsOnly, Category="Conditional")
	float Weight = 1.f;
	
	/** 
	 * If true, the binary answer will always be set to true. 
	 * This is modification No. 2 after the internal evaluation has been done.
	 */
	UPROPERTY(EditDefaultsOnly, Category="Conditional")
	bool bIsOptional = false;
	
	/**
	 * If true, after the conditional has been evaluated, the binary answer will be negated, and the fuzzy answer 
	 * will be one minus the original fuzzy answer.
	 * This is modification No. 3 after the internal evaluation has been done.
	 */
	UPROPERTY(EditDefaultsOnly, Category="Conditional")
	bool bIsInverted = false;
	
	/** 
	 * If false, after the conditional has been evaluated, the fuzzy answer will be set to 0.f if the binary answer is false.
	 * This is modification No. 4 after the internal evaluation has been done.
	 */
	UPROPERTY(EditDefaultsOnly, Category="Conditional")
	bool bDoesImpactScoreOnFail = true;
	
private:
#if WITH_EDITOR
	void UpdateTitlePropertyString();
#endif
	
#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere, meta=(EditCondition=false, EditConditionHides))
	FString ConditionalTitlePropertyString{};
#endif
};
