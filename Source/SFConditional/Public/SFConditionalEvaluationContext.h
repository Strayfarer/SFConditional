// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditionalEvaluationContext.generated.h"

struct FSFConditionalDebugTrace;

/**
 * Parameters for a conditional evaluation run.
 * 
 * Most notably contains the object to test and the evaluation instigator,
 * but also has an option for debug trace, which will be filled with evaluation info if set.
 *
 * Note that debug tracing will always be disabled in shipping builds!
 */
USTRUCT(BlueprintType)
struct SFCONDITIONAL_API FSFConditionalEvaluationContext
{
	GENERATED_BODY()

	FSFConditionalEvaluationContext() = default;

	FSFConditionalEvaluationContext(UObject* InTestObject, UObject* InInstigator = nullptr, FSFConditionalDebugTrace* InOptionalDebugTrace = nullptr) :
		TestObject(InTestObject),
		Instigator(InInstigator),
		OptionalDebugTrace(InOptionalDebugTrace)
	{}

	/** Returns the world of the test object. */
	FORCEINLINE UWorld* GetWorld() const { return TestObject->GetWorld(); }

	///// Object To Test /////

	/** Returns the test object. */
	FORCEINLINE UObject* GetTestObject() const { return TestObject; }
	
	/** Returns the test object, cast. */
	template<typename TReturnClass>
	TReturnClass* TryGetTestObjectAs() const { return Cast<TReturnClass>(TestObject); }
	
	/** 
	 * Tries to resolve the test object as actor. 
	 * Attempts casting object to AActor and casting to UActorComponent and retrieving its owner actor.
	 */
	AActor* TryGetTestObjectActor() const;
	
	/** 
	 * Tries to resolve the test object's transform. 
	 * Possible resolve paths:
	 * - cast to AActor -> actor transform
	 * - cast to USceneComponent -> scene transform
	 * - cast to UActorComponent -> get owner actor -> actor transform
	 */
	TOptional<FTransform> TryGetTestObjectTransform() const;
	
	/** 
	 * Tries to resolve an actor component from the test object.
	 * 
	 * Succeeds if the test object is a component of this class, 
	 * or if the test object as actor has a component of this class.
	 */
	template<typename TReturnClass>
	FORCEINLINE TReturnClass* TryGetTestObjectActorComponent() const;

	///// Instigator /////
	
	/** Returns the instigator. */
	FORCEINLINE UObject* GetInstigator() const { return Instigator; }
	
	/** Returns the instigator, cast. */
	template<typename TReturnClass>
	TReturnClass* TryGetInstigatorAs() const { return Cast<TReturnClass>(Instigator); }
	
	/** 
	 * Tries to resolve the instigator as actor. 
	 * Attempts casting object to AActor and casting to UActorComponent and retrieving its owner actor.
	 */
	AActor* TryGetInstigatorActor() const;
	
	/** 
	 * Tries to resolve the instigators transform. 
	 * Possible resolve paths:
	 * - cast to AActor -> actor transform
	 * - cast to USceneComponent -> scene transform
	 * - cast to UActorComponent -> get owner actor -> actor transform
	 */
	TOptional<FTransform> TryGetInstigatorTransform() const;
	
	/** 
	 * Tries to resolve an actor component from the instigator.
	 * 
	 * Succeeds if the instigator is a component of this class, 
	 * or if the instigator as actor has a component of this class.
	 */
	template<typename TReturnClass>
	FORCEINLINE TReturnClass* TryGetInstigatorActorComponent() const;

	///// Debug Trace /////
	
	FORCEINLINE FSFConditionalDebugTrace* TryGetDebugTrace() const { return OptionalDebugTrace; }

private:
	/** The object to evaluate the conditional with. */
	UPROPERTY(BlueprintReadWrite, Category="Conditional Evaluation Context", meta=(AllowPrivateAccess=true))
	TObjectPtr<UObject> TestObject = nullptr;

	/**
	 * The object that triggered the evaluation.
	 * Can be used by conditionals testing for relations between two specific objects.
	 */
	UPROPERTY(BlueprintReadWrite, Category="Conditional Evaluation Context", meta=(AllowPrivateAccess=true))
	TObjectPtr<UObject> Instigator = nullptr;
	
	FSFConditionalDebugTrace* OptionalDebugTrace;
};

////// Template Function Implementations //////

template <typename TReturnClass>
TReturnClass* FSFConditionalEvaluationContext::TryGetTestObjectActorComponent() const
{
	if (TReturnClass* ActorComponent = Cast<TReturnClass>(TestObject))
	{
		return ActorComponent;
	}
	if (const AActor* Actor = TryGetTestObjectActor())
	{
		return Actor->FindComponentByClass<TReturnClass>();
	}
	return nullptr;
}

template <typename TReturnClass>
TReturnClass* FSFConditionalEvaluationContext::TryGetInstigatorActorComponent() const
{
	if (TReturnClass* ActorComponent = Cast<TReturnClass>(Instigator))
	{
		return ActorComponent;
	}
	if (const AActor* Actor = TryGetInstigatorActor())
	{
		return Actor->FindComponentByClass<TReturnClass>();
	}
	return nullptr;
}
