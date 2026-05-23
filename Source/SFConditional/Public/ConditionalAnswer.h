// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "ConditionalAnswer.generated.h"

namespace SF
{
	class UConditional;

	/**
	 * Result of evaluating a conditional, containing both a binary and fuzzy answer.
	 * Initialized to No by default.
	 * 
	 * @see the namespace below the struct definition for various commonly used answers, especially errors.
	 */
	USTRUCT(BlueprintType)
	struct SFCONDITIONAL_API FConditionalAnswer
	{
		GENERATED_BODY()
		
		friend UConditional;

	public:
		FConditionalAnswer() = default;
		FConditionalAnswer(const bool bInBinaryAnswer, const float InFuzzyAnswer);
		explicit FConditionalAnswer(const FString& InErrorMsg);
		explicit FConditionalAnswer(const FName& InErrorMsg);

		/** Was the overall answer yes or no? */
		FORCEINLINE bool GetBinaryAnswer() const { return bBinaryAnswer; }
		/** On a scale of 0 to 1, how much was the answer yes? */
		FORCEINLINE float GetFuzzyAnswer() const { return FuzzyAnswer; }

		/** Did the evaluation yield an error? */
		FORCEINLINE bool IsError() const { return !ErrorMessage.IsNone(); }
		/** A potential error message to bubble up. */
		FORCEINLINE const FName& GetErrorMessage() const { return ErrorMessage; }

		bool operator==(const FConditionalAnswer& Other) const;

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
	namespace Conditional::Answer
	{
		/** Sets binary answer to true and fuzzy answer to 1.f. */
		SFCONDITIONAL_API const FConditionalAnswer& Yes();
		/** Sets binary answer to false and fuzzy answer to 0.f. */
		SFCONDITIONAL_API const FConditionalAnswer& No();
		
		/** Construct an answer with explicit binary and fuzzy answer. */
		SFCONDITIONAL_API FConditionalAnswer Create(const bool bBinaryAnswer, const float FuzzyAnswer);
		
		/** Sets binary answer as given and fuzzy answer to 1.f/0.f. */
		SFCONDITIONAL_API FConditionalAnswer FromBool(const bool bBooleanAnswer);

		/** Create an answer indicating an error during runtime evaluation. */
		SFCONDITIONAL_API FConditionalAnswer FromErrorMsg(const FString& InErrorMsg);
		
		/** Create an answer indicating an error during runtime evaluation. */
		SFCONDITIONAL_API FConditionalAnswer FromErrorMsg(const FName& InErrorMsg);
		
		namespace Error
		{
			SFCONDITIONAL_API const FConditionalAnswer& InvalidTestObject();
			
			SFCONDITIONAL_API const FConditionalAnswer& NumChildrenUnsupported();
			SFCONDITIONAL_API const FConditionalAnswer& HasInvalidChild();
			SFCONDITIONAL_API const FConditionalAnswer& HasChildWithRuntimeError();
			
			SFCONDITIONAL_API FConditionalAnswer NoPlayerController(const UWorld* World);
			SFCONDITIONAL_API FConditionalAnswer NoViewport(const APlayerController* Pc);
			
			namespace TestObject
			{
				SFCONDITIONAL_API FConditionalAnswer NoActor(const UObject* TestObject);
				SFCONDITIONAL_API FConditionalAnswer NoActorComponent(const UObject* TestObject);
				SFCONDITIONAL_API FConditionalAnswer NoSceneComponent(const UObject* TestObject);
				
				SFCONDITIONAL_API FConditionalAnswer NoActorProvider(const UObject* TestObject);
				SFCONDITIONAL_API FConditionalAnswer NoTransformProvider(const UObject* TestObject);
			}
			namespace Instigator
			{
				SFCONDITIONAL_API FConditionalAnswer NoActor(const UObject* TestObject);
				SFCONDITIONAL_API FConditionalAnswer NoActorComponent(const UObject* TestObject);
				SFCONDITIONAL_API FConditionalAnswer NoSceneComponent(const UObject* TestObject);
				
				SFCONDITIONAL_API FConditionalAnswer NoActorProvider(const UObject* TestObject);
				SFCONDITIONAL_API FConditionalAnswer NoTransformProvider(const UObject* TestObject);
			}
		}
	}
}
