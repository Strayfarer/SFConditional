// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalBlueprintFunctionLibrary.h"

#include "ConditionalEvaluationContext.h"
#include "ConditionalDebugTrace.h"

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_FromBool(const bool bBooleanAnswer)
{
	return Conditional::Answer::FromBool(bBooleanAnswer);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_FromString(const FString InErrorMsg)
{
	return Conditional::Answer::FromErrorMsg(InErrorMsg);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_FromName(const FName InErrorMsg)
{
	return Conditional::Answer::FromErrorMsg(InErrorMsg);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Yes()
{
	return Conditional::Answer::Yes();
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_No()
{
	return Conditional::Answer::No();
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_HasChildWithRuntimeError()
{
	return Conditional::Answer::Error::HasChildWithRuntimeError();
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_NoPlayerController(const UWorld* World)
{
	return Conditional::Answer::Error::NoPlayerController(World);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_NoViewport(const APlayerController* Pc)
{
	return Conditional::Answer::Error::NoViewport(Pc);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoActor(const UObject* TestObject)
{
	return Conditional::Answer::Error::TestObject::NoActor(TestObject);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoActorComponent(const UObject* TestObject)
{
	return Conditional::Answer::Error::TestObject::NoActorComponent(TestObject);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoSceneComponent(const UObject* TestObject)
{
	return Conditional::Answer::Error::TestObject::NoSceneComponent(TestObject);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoActorProvider(const UObject* TestObject)
{
	return Conditional::Answer::Error::TestObject::NoActorProvider(TestObject);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoTransform(const UObject* TestObject)
{
	return Conditional::Answer::Error::TestObject::NoTransformProvider(TestObject);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoActor(const UObject* Instigator)
{
	return Conditional::Answer::Error::Instigator::NoActor(Instigator);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoActorComponent(const UObject* Instigator)
{
	return Conditional::Answer::Error::Instigator::NoActorComponent(Instigator);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoSceneComponent(const UObject* Instigator)
{
	return Conditional::Answer::Error::Instigator::NoSceneComponent(Instigator);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoActorProvider(const UObject* Instigator)
{
	return Conditional::Answer::Error::Instigator::NoActorProvider(Instigator);
}

SF::FConditionalAnswer SF::UConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoTransform(const UObject* Instigator)
{
	return Conditional::Answer::Error::Instigator::NoTransformProvider(Instigator);
}

bool SF::UConditionalBlueprintFunctionLibrary::Answer_GetBinaryAnswer(const FConditionalAnswer& Answer)
{
	return Answer.GetBinaryAnswer();
}

float SF::UConditionalBlueprintFunctionLibrary::Answer_GetFuzzyAnswer(const FConditionalAnswer& Answer)
{
	return Answer.GetFuzzyAnswer();
}

FString SF::UConditionalBlueprintFunctionLibrary::DebugTrace_ToString(const FConditionalDebugTrace& DebugTrace)
{
	return DebugTrace.ToString();
}

UWorld* SF::UConditionalBlueprintFunctionLibrary::EvaluationContext_GetWorld(
	const FConditionalEvaluationContext& EvaluationContext)
{
	return EvaluationContext.GetWorld();
}

UObject* SF::UConditionalBlueprintFunctionLibrary::EvaluationContext_GetTestObject(
	const FConditionalEvaluationContext& EvaluationContext)
{
	return EvaluationContext.GetTestObject();
}

UObject* SF::UConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetTestObjectAs(
	const FConditionalEvaluationContext& EvaluationContext, const TSubclassOf<UObject> ReturnClass)
{
	UObject* TestObject = EvaluationContext.GetTestObject();
	if (!TestObject)
		return nullptr;
	if (!TestObject->IsA(ReturnClass))
		return nullptr;
	return TestObject;
}

AActor* SF::UConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetTestObjectActor(
	const FConditionalEvaluationContext& EvaluationContext)
{
	return EvaluationContext.TryGetTestObjectActor();
}

FTransform SF::UConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetTestObjectTransform(
	const FConditionalEvaluationContext& EvaluationContext, bool& bOutWasSuccess)
{
	const TOptional<FTransform> Transform = EvaluationContext.TryGetTestObjectTransform();
	bOutWasSuccess = Transform.IsSet();
	return Transform.Get(FTransform::Identity);
}

UObject* SF::UConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetTestObjectActorComponent(
	const FConditionalEvaluationContext& EvaluationContext, const TSubclassOf<UActorComponent> ReturnClass)
{
	if (const AActor* Actor = EvaluationContext.TryGetTestObjectActor())
	{
		return Actor->FindComponentByClass(ReturnClass);
	}
	return nullptr;
}

UObject* SF::UConditionalBlueprintFunctionLibrary::EvaluationContext_GetInstigator(
	const FConditionalEvaluationContext& EvaluationContext)
{
	return EvaluationContext.GetInstigator();
}

UObject* SF::UConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetInstigatorAs(
	const FConditionalEvaluationContext& EvaluationContext, const TSubclassOf<UObject> ReturnClass)
{
	UObject* Instigator = EvaluationContext.GetInstigator();
	if (!Instigator)
		return nullptr;
	if (!Instigator->IsA(ReturnClass))
		return nullptr;
	return Instigator;
}

AActor* SF::UConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetInstigatorActor(
	const FConditionalEvaluationContext& EvaluationContext)
{
	return EvaluationContext.TryGetInstigatorActor();
}

FTransform SF::UConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetInstigatorTransform(
	const FConditionalEvaluationContext& EvaluationContext, bool& bOutWasSuccess)
{
	const TOptional<FTransform> Transform = EvaluationContext.TryGetInstigatorTransform();
	bOutWasSuccess = Transform.IsSet();
	return Transform.Get(FTransform::Identity);
}

UObject* SF::UConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetInstigatorActorComponent(
	const FConditionalEvaluationContext& EvaluationContext, const TSubclassOf<UActorComponent> ReturnClass)
{
	if (const AActor* Actor = EvaluationContext.TryGetInstigatorActor())
	{
		return Actor->FindComponentByClass(ReturnClass);
	}
	return nullptr;
}
