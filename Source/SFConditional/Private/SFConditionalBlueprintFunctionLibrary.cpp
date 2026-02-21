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

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_NoPlayerController()
{
	return SF::Conditional::Answer::Error::NoPlayerController();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_NoViewport()
{
	return SF::Conditional::Answer::Error::NoViewport();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoActor()
{
	return SF::Conditional::Answer::Error::TestObject::NoActor();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoActorComponent()
{
	return SF::Conditional::Answer::Error::TestObject::NoActorComponent();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoSceneComponent()
{
	return SF::Conditional::Answer::Error::TestObject::NoSceneComponent();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoActorProvider()
{
	return SF::Conditional::Answer::Error::TestObject::NoActorProvider();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_TestObject_NoTransform()
{
	return SF::Conditional::Answer::Error::TestObject::NoTransformProvider();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoActor()
{
	return SF::Conditional::Answer::Error::Instigator::NoActor();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoActorComponent()
{
	return SF::Conditional::Answer::Error::Instigator::NoActorComponent();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoSceneComponent()
{
	return SF::Conditional::Answer::Error::Instigator::NoSceneComponent();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoActorProvider()
{
	return SF::Conditional::Answer::Error::Instigator::NoActorProvider();
}

FSFConditionalAnswer USFConditionalBlueprintFunctionLibrary::Answer_Error_Instigator_NoTransform()
{
	return SF::Conditional::Answer::Error::Instigator::NoTransformProvider();
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
