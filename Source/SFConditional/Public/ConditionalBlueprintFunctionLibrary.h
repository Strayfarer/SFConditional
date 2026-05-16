// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "ConditionalAnswer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConditionalBlueprintFunctionLibrary.generated.h"

namespace SF
{
	struct FConditionalEvaluationContext;
	struct FConditionalDebugTrace;

	/**
	 * Blueprint utilities for conditionals.
	 */
	UCLASS()
	class SFCONDITIONAL_API UConditionalBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
	{
		GENERATED_BODY()

	public:
		///// Conditional Answer /////

		// Constructors

		/** Sets binary answer as given and fuzzy answer to 1.f/0.f. */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer",
			meta=(DisplayName="Make Conditional Answer - From Bool"))
		static FConditionalAnswer Answer_FromBool(const bool bBooleanAnswer);

		/** Create an answer indicating an error during runtime evaluation. */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error",
			meta=(DisplayName="Make Conditional Error - From String"))
		static FConditionalAnswer Answer_Error_FromString(const FString InErrorMsg);

		/** Create an answer indicating an error during runtime evaluation. */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error",
			meta=(DisplayName="Make Conditional Error - From Name"))
		static FConditionalAnswer Answer_Error_FromName(const FName InErrorMsg);

		// Predefined

		/** Sets binary answer to true and fuzzy answer to 1.f. */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer",
			meta=(DisplayName="Make Conditional Answer - Yes"))
		static FConditionalAnswer Answer_Yes();

		/** Sets binary answer to false and fuzzy answer to 0.f. */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer",
			meta=(DisplayName="Make Conditional Answer - No"))
		static FConditionalAnswer Answer_No();

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error",
			meta=(DisplayName="Make Conditional Error - Has Child With Runtime Error"))
		static FConditionalAnswer Answer_Error_HasChildWithRuntimeError();

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error",
			meta=(DisplayName="Make Conditional Error - No Player Controller"))
		static FConditionalAnswer Answer_Error_NoPlayerController(const UWorld* World);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error",
			meta=(DisplayName="Make Conditional Error - No Viewport"))
		static FConditionalAnswer Answer_Error_NoViewport(const APlayerController* Pc);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|TestObject",
			meta=(DisplayName="Make Conditional Error - TestObject - No Actor"))
		static FConditionalAnswer Answer_Error_TestObject_NoActor(const UObject* TestObject);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|TestObject",
			meta=(DisplayName="Make Conditional Error - TestObject - No ActorComponent"))
		static FConditionalAnswer Answer_Error_TestObject_NoActorComponent(const UObject* TestObject);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|TestObject",
			meta=(DisplayName="Make Conditional Error - TestObject - No SceneComponent"))
		static FConditionalAnswer Answer_Error_TestObject_NoSceneComponent(const UObject* TestObject);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|TestObject",
			meta=(DisplayName="Make Conditional Error - TestObject - No Actor Provider"))
		static FConditionalAnswer Answer_Error_TestObject_NoActorProvider(const UObject* TestObject);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|TestObject",
			meta=(DisplayName="Make Conditional Error - TestObject - No Transform Provider"))
		static FConditionalAnswer Answer_Error_TestObject_NoTransform(const UObject* TestObject);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|Instigator",
			meta=(DisplayName="Make Conditional Error - Instigator - No Actor"))
		static FConditionalAnswer Answer_Error_Instigator_NoActor(const UObject* Instigator);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|Instigator",
			meta=(DisplayName="Make Conditional Error - Instigator - No ActorComponent"))
		static FConditionalAnswer Answer_Error_Instigator_NoActorComponent(const UObject* Instigator);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|Instigator",
			meta=(DisplayName="Make Conditional Error - Instigator - No SceneComponent"))
		static FConditionalAnswer Answer_Error_Instigator_NoSceneComponent(const UObject* Instigator);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|Instigator",
			meta=(DisplayName="Make Conditional Error - Instigator - No Actor Provider"))
		static FConditionalAnswer Answer_Error_Instigator_NoActorProvider(const UObject* Instigator);

		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|Instigator",
			meta=(DisplayName="Make Conditional Error - Instigator - No Transform Provider"))
		static FConditionalAnswer Answer_Error_Instigator_NoTransform(const UObject* Instigator);

		// Getters

		/** Was the overall answer yes or no? */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer",
			meta=(DisplayName="Get Binary Answer"))
		static bool Answer_GetBinaryAnswer(const FConditionalAnswer& Answer);

		/** On a scale of 0 to 1, how much was the answer yes? */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer",
			meta=(DisplayName="Get Fuzzy Answer"))
		static float Answer_GetFuzzyAnswer(const FConditionalAnswer& Answer);

		///// Conditional Debug Trace /////

		/** Build and return the string of the current trace state. */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Debug Trace", DisplayName="To String")
		static FString DebugTrace_ToString(const FConditionalDebugTrace& DebugTrace);

		///// Conditional Evaluation Context /////

		/** Returns the world of the test object. */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context", DisplayName="Get World")
		static UWorld* EvaluationContext_GetWorld(const FConditionalEvaluationContext& EvaluationContext);

		/** Returns the test object. */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context",
			DisplayName="Get TestObject")
		static UObject* EvaluationContext_GetTestObject(const FConditionalEvaluationContext& EvaluationContext);

		/** Returns the test object, cast. */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context",
			DisplayName="Try Get TestObject As", meta=(DeterminesOutputType="ReturnClass"))
		static UObject* EvaluationContext_TryGetTestObjectAs
		(
			const FConditionalEvaluationContext& EvaluationContext,
			const TSubclassOf<UObject> ReturnClass
		);

		/** 
		 * Tries to resolve the test object as actor. 
		 * Attempts casting object to AActor and casting to UActorComponent and retrieving its owner actor.
		 */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context",
			DisplayName="Try Get TestObject Actor")
		static AActor* EvaluationContext_TryGetTestObjectActor(const FConditionalEvaluationContext& EvaluationContext);

		/** 
		 * Tries to resolve the test object's transform. 
		 * Possible resolve paths:
		 * - cast to AActor -> actor transform
		 * - cast to USceneComponent -> scene transform
		 * - cast to UActorComponent -> get owner actor -> actor transform
		 */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context",
			DisplayName="Try Get TestObject Transform")
		static FTransform EvaluationContext_TryGetTestObjectTransform
		(
			const FConditionalEvaluationContext& EvaluationContext,
			UPARAM(DisplayName="Was Success") bool& bOutWasSuccess
		);

		/** 
		 * Tries to resolve an actor component from the test object.
		 * 
		 * Succeeds if the test object is a component of this class, 
		 * or if the test object as actor has a component of this class.
		 */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context",
			DisplayName="Try Get TestObject ActorComponent", meta=(DeterminesOutputType="ReturnClass"))
		static UObject* EvaluationContext_TryGetTestObjectActorComponent
		(
			const FConditionalEvaluationContext& EvaluationContext,
			const TSubclassOf<UActorComponent> ReturnClass
		);

		/** Returns the instigator. */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context",
			DisplayName="Get Instigator")
		static UObject* EvaluationContext_GetInstigator(const FConditionalEvaluationContext& EvaluationContext);

		/** Returns the instigator, cast to ReturnClass. */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context",
			DisplayName="Try Get Instigator As", meta=(DeterminesOutputType="ReturnClass"))
		static UObject* EvaluationContext_TryGetInstigatorAs
		(
			const FConditionalEvaluationContext& EvaluationContext,
			const TSubclassOf<UObject> ReturnClass
		);

		/** 
		 * Tries to resolve the instigator as actor. 
		 * Attempts casting object to AActor and casting to UActorComponent and retrieving its owner actor.
		 */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context",
			DisplayName="Try Get Instigator Actor")
		static AActor* EvaluationContext_TryGetInstigatorActor(const FConditionalEvaluationContext& EvaluationContext);

		/** 
		 * Tries to resolve the instigators transform. 
		 * Possible resolve paths:
		 * - cast to AActor -> actor transform
		 * - cast to USceneComponent -> scene transform
		 * - cast to UActorComponent -> get owner actor -> actor transform
		 */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context",
			DisplayName="Try Get Instigator Transform")
		static FTransform EvaluationContext_TryGetInstigatorTransform
		(
			const FConditionalEvaluationContext& EvaluationContext,
			UPARAM(DisplayName="Was Success") bool& bOutWasSuccess
		);

		/** 
		 * Tries to resolve an actor component from the instigator.
		 * 
		 * Succeeds if the instigator is a component of this class, 
		 * or if the instigator as actor has a component of this class.
		 */
		UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context",
			DisplayName="Try Get Instigator ActorComponent", meta=(DeterminesOutputType="ReturnClass"))
		static UObject* EvaluationContext_TryGetInstigatorActorComponent
		(
			const FConditionalEvaluationContext& EvaluationContext,
			const TSubclassOf<UActorComponent> ReturnClass
		);
	};
}
