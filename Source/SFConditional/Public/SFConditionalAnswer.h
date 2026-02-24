// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditionalAnswer.generated.h"

class USFConditional;

/**
 * Result of evaluating a conditional, containing both a binary and fuzzy answer.
 * Initialized to No by default.
 * 
 * @see the namespace below the struct definition for various commonly used answers, especially errors.
 */
USTRUCT(BlueprintType)
struct SFCONDITIONAL_API FSFConditionalAnswer
{
	GENERATED_BODY()

	friend USFConditional;
	
public:
	FSFConditionalAnswer() = default;
	FSFConditionalAnswer(const bool bInBinaryAnswer, const float InFuzzyAnswer);
	explicit FSFConditionalAnswer(const FString& InErrorMsg);
	explicit FSFConditionalAnswer(const FName& InErrorMsg);

	/** Was the overall answer yes or no? */
	FORCEINLINE bool GetBinaryAnswer() const { return bBinaryAnswer; }
	/** On a scale of 0 to 1, how much was the answer yes? */
	FORCEINLINE float GetFuzzyAnswer() const { return FuzzyAnswer; }
	
	/** Did the evaluation yield an error? */
	FORCEINLINE bool IsError() const { return !ErrorMessage.IsNone(); }
	/** A potential error message to bubble up. */
	FORCEINLINE const FName& GetErrorMessage() const { return ErrorMessage; }
	
	bool operator==(const FSFConditionalAnswer& Other) const;

private:
	/** Was the overall answer yes or no? */
	UPROPERTY(BlueprintReadWrite, Category="SFConditional Answer", meta=(AllowPrivateAccess=true))
	bool bBinaryAnswer = false;
	
	/** On a scale of 0 to 1, how much was the answer yes? */
	UPROPERTY(BlueprintReadWrite, Category="SFConditional Answer", meta=(AllowPrivateAccess=true))
	float FuzzyAnswer = 0.f;
	
	/** A potential error message to bubble up. */
	UPROPERTY(BlueprintReadWrite, Category="SFConditional Answer", meta=(AllowPrivateAccess=true))
	FName ErrorMessage = {};
};


// commonly used constructors and predefined answers
namespace SF::Conditional::Answer
{
	/** Sets binary answer to true and fuzzy answer to 1.f. */
	SFCONDITIONAL_API const FSFConditionalAnswer& Yes();
	/** Sets binary answer to false and fuzzy answer to 0.f. */
	SFCONDITIONAL_API const FSFConditionalAnswer& No();
	
	/** Construct an answer with explicit binary and fuzzy answer. */
	SFCONDITIONAL_API FSFConditionalAnswer Create(const bool bBinaryAnswer, const float FuzzyAnswer);
	
	/** Sets binary answer as given and fuzzy answer to 1.f/0.f. */
	SFCONDITIONAL_API FSFConditionalAnswer FromBool(const bool bBooleanAnswer);

	/** Create an answer indicating an error during runtime evaluation. */
	SFCONDITIONAL_API FSFConditionalAnswer FromErrorMsg(const FString& InErrorMsg);
	
	/** Create an answer indicating an error during runtime evaluation. */
	SFCONDITIONAL_API FSFConditionalAnswer FromErrorMsg(const FName& InErrorMsg);
	
	namespace Error
	{
		SFCONDITIONAL_API const FSFConditionalAnswer& InvalidTestObject();
		
		SFCONDITIONAL_API const FSFConditionalAnswer& NumChildrenUnsupported();
		SFCONDITIONAL_API const FSFConditionalAnswer& HasInvalidChild();
		SFCONDITIONAL_API const FSFConditionalAnswer& HasChildWithRuntimeError();
		
		SFCONDITIONAL_API const FSFConditionalAnswer& NoPlayerController(const UWorld* World);
		SFCONDITIONAL_API const FSFConditionalAnswer& NoViewport(const APlayerController* Pc);
		
		namespace TestObject
		{
			SFCONDITIONAL_API const FSFConditionalAnswer& NoActor(const UObject* TestObject);
			SFCONDITIONAL_API const FSFConditionalAnswer& NoActorComponent(const UObject* TestObject);
			SFCONDITIONAL_API const FSFConditionalAnswer& NoSceneComponent(const UObject* TestObject);
			
			SFCONDITIONAL_API const FSFConditionalAnswer& NoActorProvider(const UObject* TestObject);
			SFCONDITIONAL_API const FSFConditionalAnswer& NoTransformProvider(const UObject* TestObject);
		}
		namespace Instigator
		{
			SFCONDITIONAL_API const FSFConditionalAnswer& NoActor(const UObject* TestObject);
			SFCONDITIONAL_API const FSFConditionalAnswer& NoActorComponent(const UObject* TestObject);
			SFCONDITIONAL_API const FSFConditionalAnswer& NoSceneComponent(const UObject* TestObject);
			
			SFCONDITIONAL_API const FSFConditionalAnswer& NoActorProvider(const UObject* TestObject);
			SFCONDITIONAL_API const FSFConditionalAnswer& NoTransformProvider(const UObject* TestObject);
		}
	}
}
