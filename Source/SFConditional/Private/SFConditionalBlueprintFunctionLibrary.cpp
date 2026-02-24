// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "SFConditionalBlueprintFunctionLibrary.h"

#include "SFConditionalEvaluationContext.h"
#include "SFConditionalDebugTrace.h"

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_FromBool(const bool bBooleanAnswer)
{
	return SF::Conditional::Answer::FromBool(bBooleanAnswer);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_FromString(const FString InErrorMsg)
{
	return SF::Conditional::Answer::FromErrorMsg(InErrorMsg);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_FromName(const FName InErrorMsg)
{
	return SF::Conditional::Answer::FromErrorMsg(InErrorMsg);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Yes()
{
	return SF::Conditional::Answer::Yes();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_No()
{
	return SF::Conditional::Answer::No();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_HasChildWithRuntimeError()
{
	return SF::Conditional::Answer::Error::HasChildWithRuntimeError();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_NoPlayerController(const UWorld* World)
{
	return SF::Conditional::Answer::Error::NoPlayerController(World);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_NoViewport(const APlayerController* Pc)
{
	return SF::Conditional::Answer::Error::NoViewport(Pc);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoActor(const UObject* TestObject)
{
	return SF::Conditional::Answer::Error::TestObject::NoActor(TestObject);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoActorComponent(const UObject* TestObject)
{
	return SF::Conditional::Answer::Error::TestObject::NoActorComponent(TestObject);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoSceneComponent(const UObject* TestObject)
{
	return SF::Conditional::Answer::Error::TestObject::NoSceneComponent(TestObject);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoActorProvider(const UObject* TestObject)
{
	return SF::Conditional::Answer::Error::TestObject::NoActorProvider(TestObject);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoTransform(const UObject* TestObject)
{
	return SF::Conditional::Answer::Error::TestObject::NoTransformProvider(TestObject);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoActor(const UObject* Instigator)
{
	return SF::Conditional::Answer::Error::Instigator::NoActor(Instigator);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoActorComponent(const UObject* Instigator)
{
	return SF::Conditional::Answer::Error::Instigator::NoActorComponent(Instigator);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoSceneComponent(const UObject* Instigator)
{
	return SF::Conditional::Answer::Error::Instigator::NoSceneComponent(Instigator);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoActorProvider(const UObject* Instigator)
{
	return SF::Conditional::Answer::Error::Instigator::NoActorProvider(Instigator);
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoTransform(const UObject* Instigator)
{
	return SF::Conditional::Answer::Error::Instigator::NoTransformProvider(Instigator);
}

bool USFConditionalBlueprintFunctionLibrary::Answer_GetBinaryAnswer(const FSFConditionalAnswer& Answer)
{
	return Answer.GetBinaryAnswer();
}

float USFConditionalBlueprintFunctionLibrary::Answer_GetFuzzyAnswer(const FSFConditionalAnswer& Answer)
{
	return Answer.GetFuzzyAnswer();
}

FString USFConditionalBlueprintFunctionLibrary::DebugTrace_ToString(const FSFConditionalDebugTrace& DebugTrace)
{
	return DebugTrace.ToString();
}

UWorld* USFConditionalBlueprintFunctionLibrary::EvaluationContext_GetWorld(
	const FSFConditionalEvaluationContext& EvaluationContext)
{
	return EvaluationContext.GetWorld();
}

UObject* USFConditionalBlueprintFunctionLibrary::EvaluationContext_GetTestObject(
	const FSFConditionalEvaluationContext& EvaluationContext)
{
	return EvaluationContext.GetTestObject();
}

UObject* USFConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetTestObjectAs(
	const FSFConditionalEvaluationContext& EvaluationContext, const TSubclassOf<UObject> ReturnClass)
{
	return EvaluationContext.GetTestObject();
}

AActor* USFConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetTestObjectActor(
	const FSFConditionalEvaluationContext& EvaluationContext)
{
	return EvaluationContext.TryGetTestObjectActor();
}

FTransform USFConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetTestObjectTransform(
	const FSFConditionalEvaluationContext& EvaluationContext, bool& bOutWasSuccess)
{
	const TOptional<FTransform> Transform = EvaluationContext.TryGetTestObjectTransform();
	bOutWasSuccess = Transform.IsSet();
	return Transform.Get(FTransform::Identity);
}

UObject* USFConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetTestObjectActorComponent(
	const FSFConditionalEvaluationContext& EvaluationContext, const TSubclassOf<UActorComponent> ReturnClass)
{
	return EvaluationContext.TryGetTestObjectActor()->FindComponentByClass(ReturnClass);
}

UObject* USFConditionalBlueprintFunctionLibrary::EvaluationContext_GetInstigator(
	const FSFConditionalEvaluationContext& EvaluationContext)
{
	return EvaluationContext.GetInstigator();
}

UObject* USFConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetInstigatorAs(
	const FSFConditionalEvaluationContext& EvaluationContext, const TSubclassOf<UObject> ReturnClass)
{
	return EvaluationContext.GetInstigator();
}

AActor* USFConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetInstigatorActor(
	const FSFConditionalEvaluationContext& EvaluationContext)
{
	return EvaluationContext.TryGetInstigatorActor();
}

FTransform USFConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetInstigatorTransform(
	const FSFConditionalEvaluationContext& EvaluationContext, bool& bOutWasSuccess)
{
	const TOptional<FTransform> Transform = EvaluationContext.TryGetInstigatorTransform();
	bOutWasSuccess = Transform.IsSet();
	return Transform.Get(FTransform::Identity);
}

UObject* USFConditionalBlueprintFunctionLibrary::EvaluationContext_TryGetInstigatorActorComponent(
	const FSFConditionalEvaluationContext& EvaluationContext, const TSubclassOf<UActorComponent> ReturnClass)
{
	return EvaluationContext.TryGetInstigatorActor()->FindComponentByClass(ReturnClass);
}
