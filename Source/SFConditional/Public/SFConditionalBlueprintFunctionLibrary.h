// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditionalAnswer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SFConditionalBlueprintFunctionLibrary.generated.h"

struct FSFConditionalEvaluationContext;
struct FSFConditionalDebugTrace;

/**
 * Blueprint utilities for conditionals.
 */
UCLASS()
class SFCONDITIONAL_API USFConditionalBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	///// Conditional Answer /////
	
	// Constructors
	
	/** Sets binary answer as given and fuzzy answer to 1.f/0.f. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer", meta=(DisplayName="Make Conditional Answer - From Bool"))
	static FSFConditionalAnswer Answer_FromBool(const bool bBooleanAnswer);

	/** Create an answer indicating an error during runtime evaluation. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error", meta=(DisplayName="Make Conditional Error - From String"))
	static FSFConditionalAnswer Answer_Error_FromString(const FString InErrorMsg);

	/** Create an answer indicating an error during runtime evaluation. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error", meta=(DisplayName="Make Conditional Error - From Name"))
	static FSFConditionalAnswer Answer_Error_FromName(const FName InErrorMsg);
	
	// Predefined
	
	/** Sets binary answer to true and fuzzy answer to 1.f. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer", meta=(DisplayName="Make Conditional Answer - Yes"))
	static FSFConditionalAnswer Answer_Yes();
	
	/** Sets binary answer to false and fuzzy answer to 0.f. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer", meta=(DisplayName="Make Conditional Answer - No"))
	static FSFConditionalAnswer Answer_No();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error", meta=(DisplayName="Make Conditional Error - No Player Controller"))
	static FSFConditionalAnswer Answer_Error_NoPlayerController();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error", meta=(DisplayName="Make Conditional Error - No Viewport"))
	static FSFConditionalAnswer Answer_Error_NoViewport();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|TestObject", meta=(DisplayName="Make Conditional Error - TestObject - No Actor"))
	static FSFConditionalAnswer Answer_Error_TestObject_NoActor();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|TestObject", meta=(DisplayName="Make Conditional Error - TestObject - No ActorComponent"))
	static FSFConditionalAnswer Answer_Error_TestObject_NoActorComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|TestObject", meta=(DisplayName="Make Conditional Error - TestObject - No SceneComponent"))
	static FSFConditionalAnswer Answer_Error_TestObject_NoSceneComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|TestObject", meta=(DisplayName="Make Conditional Error - TestObject - No Actor Provider"))
	static FSFConditionalAnswer Answer_Error_TestObject_NoActorProvider();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|TestObject", meta=(DisplayName="Make Conditional Error - TestObject - No Transform Provider"))
	static FSFConditionalAnswer Answer_Error_TestObject_NoTransform();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|Instigator", meta=(DisplayName="Make Conditional Error - Instigator - No Actor"))
	static FSFConditionalAnswer Answer_Error_Instigator_NoActor();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|Instigator", meta=(DisplayName="Make Conditional Error - Instigator - No ActorComponent"))
	static FSFConditionalAnswer Answer_Error_Instigator_NoActorComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|Instigator", meta=(DisplayName="Make Conditional Error - Instigator - No SceneComponent"))
	static FSFConditionalAnswer Answer_Error_Instigator_NoSceneComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|Instigator", meta=(DisplayName="Make Conditional Error - Instigator - No Actor Provider"))
	static FSFConditionalAnswer Answer_Error_Instigator_NoActorProvider();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer|Error|Instigator", meta=(DisplayName="Make Conditional Error - Instigator - No Transform Provider"))
	static FSFConditionalAnswer Answer_Error_Instigator_NoTransform();
	
	// Getters

	/** Was the overall answer yes or no? */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer", meta=(DisplayName="Get Binary Answer"))
	static bool Answer_GetBinaryAnswer(const FSFConditionalAnswer& Answer);
	
	/** On a scale of 0 to 1, how much was the answer yes? */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Answer", meta=(DisplayName="Get Fuzzy Answer"))
	static float Answer_GetFuzzyAnswer(const FSFConditionalAnswer& Answer);
	
	///// Conditional Debug Trace /////

	/** Build and return the string of the current trace state. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Debug Trace", DisplayName="To String")
	static FString DebugTrace_ToString(const FSFConditionalDebugTrace& DebugTrace);
	
	///// Conditional Evaluation Context /////

	/** Returns the world of the test object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context", DisplayName="Get World")
	static UWorld* EvaluationContext_GetWorld(const FSFConditionalEvaluationContext& EvaluationContext);
	
	/** Returns the test object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context", DisplayName="Get TestObject")
	static UObject* EvaluationContext_GetTestObject(const FSFConditionalEvaluationContext& EvaluationContext);
	
	/** Returns the test object, cast. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context", DisplayName="Try Get TestObject As", meta=(DeterminesOutputType="ReturnClass"))
	static UObject* EvaluationContext_TryGetTestObjectAs
	(
		const FSFConditionalEvaluationContext& EvaluationContext, 
		const TSubclassOf<UObject> ReturnClass
	);
	
	/** 
	 * Tries to resolve the test object as actor. 
	 * Attempts casting object to AActor and casting to UActorComponent and retrieving its owner actor.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context", DisplayName="Try Get TestObject Actor")
	static AActor* EvaluationContext_TryGetTestObjectActor(const FSFConditionalEvaluationContext& EvaluationContext);
	
	/** 
	 * Tries to resolve the test object's transform. 
	 * Possible resolve paths:
	 * - cast to AActor -> actor transform
	 * - cast to USceneComponent -> scene transform
	 * - cast to UActorComponent -> get owner actor -> actor transform
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context", DisplayName="Try Get TestObject Transform")
	static FTransform EvaluationContext_TryGetTestObjectTransform
	(
		const FSFConditionalEvaluationContext& EvaluationContext, 
		UPARAM(DisplayName="Was Success") bool& bOutWasSuccess
	);
	
	/** 
	 * Tries to resolve an actor component from the test object.
	 * 
	 * Succeeds if the test object is a component of this class, 
	 * or if the test object as actor has a component of this class.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context", DisplayName="Try Get TestObject ActorComponent", meta=(DeterminesOutputType="ReturnClass"))
	static UObject* EvaluationContext_TryGetTestObjectActorComponent
	(
		const FSFConditionalEvaluationContext& EvaluationContext, 
		const TSubclassOf<UActorComponent> ReturnClass
	);
	
	/** Returns the instigator. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context", DisplayName="Get Instigator")
	static UObject* EvaluationContext_GetInstigator(const FSFConditionalEvaluationContext& EvaluationContext);
	
	/** Returns the instigator, cast to ReturnClass. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context", DisplayName="Try Get Instigator As", meta=(DeterminesOutputType="ReturnClass"))
	static UObject* EvaluationContext_TryGetInstigatorAs
	(
		const FSFConditionalEvaluationContext& EvaluationContext, 
		const TSubclassOf<UObject> ReturnClass
	);
	
	/** 
	 * Tries to resolve the instigator as actor. 
	 * Attempts casting object to AActor and casting to UActorComponent and retrieving its owner actor.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context", DisplayName="Try Get Instigator Actor")
	static AActor* EvaluationContext_TryGetInstigatorActor(const FSFConditionalEvaluationContext& EvaluationContext);
	
	/** 
	 * Tries to resolve the instigators transform. 
	 * Possible resolve paths:
	 * - cast to AActor -> actor transform
	 * - cast to USceneComponent -> scene transform
	 * - cast to UActorComponent -> get owner actor -> actor transform
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context", DisplayName="Try Get Instigator Transform")
	static FTransform EvaluationContext_TryGetInstigatorTransform
	(
		const FSFConditionalEvaluationContext& EvaluationContext, 
		UPARAM(DisplayName="Was Success") bool& bOutWasSuccess
	);
	
	/** 
	 * Tries to resolve an actor component from the instigator.
	 * 
	 * Succeeds if the instigator is a component of this class, 
	 * or if the instigator as actor has a component of this class.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Conditional|Evaluation Context", DisplayName="Try Get Instigator ActorComponent", meta=(DeterminesOutputType="ReturnClass"))
	static UObject* EvaluationContext_TryGetInstigatorActorComponent
	(
		const FSFConditionalEvaluationContext& EvaluationContext, 
		const TSubclassOf<UActorComponent> ReturnClass
	);
};
