// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "SFConditionalAnswer.h"

FSFConditionalAnswer::FSFConditionalAnswer(const bool bInBinaryAnswer, const float InFuzzyAnswer)
	: bBinaryAnswer(bInBinaryAnswer), FuzzyAnswer(InFuzzyAnswer) {}

FSFConditionalAnswer::FSFConditionalAnswer(const FString& InErrorMsg) 
	: ErrorMessage(InErrorMsg) {}

FSFConditionalAnswer::FSFConditionalAnswer(const FName& InErrorMsg)
	: ErrorMessage(InErrorMsg) {}

bool FSFConditionalAnswer::operator==(const FSFConditionalAnswer& Other) const
{
	return ErrorMessage == Other.ErrorMessage
		|| (bBinaryAnswer == Other.bBinaryAnswer && FMath::IsNearlyEqual(FuzzyAnswer, Other.FuzzyAnswer));
}

const FSFConditionalAnswer& SF::Conditional::Answer::Yes()
{
    static FSFConditionalAnswer Instance(true, 1.f);
	return Instance;
}

const FSFConditionalAnswer& SF::Conditional::Answer::No()
{
	static FSFConditionalAnswer Instance{ false, 0.f };
	return Instance;
}

FSFConditionalAnswer SF::Conditional::Answer::Create(const bool bBinaryAnswer, const float FuzzyAnswer)
{
	return FSFConditionalAnswer(bBinaryAnswer, FuzzyAnswer);
}

FSFConditionalAnswer SF::Conditional::Answer::FromBool(const bool bBooleanAnswer)
{
	return FSFConditionalAnswer(bBooleanAnswer, bBooleanAnswer ? 1.f : 0.f);
}

FSFConditionalAnswer SF::Conditional::Answer::FromErrorMsg(const FString& InErrorMsg)
{
	return FSFConditionalAnswer(InErrorMsg);
}

FSFConditionalAnswer SF::Conditional::Answer::FromErrorMsg(const FName& InErrorMsg)
{
	return FSFConditionalAnswer(InErrorMsg.ToString());
}

#define SF_CONDITIONAL_IMPL_ERROR(ErrorMsg) \
	static FSFConditionalAnswer Instance{ FName(ErrorMsg) }; \
return Instance;

#define SF_CONDITIONAL_IMPL_ERROR_OBJ(ErrorMsg, Object) \
	static FSFConditionalAnswer Instance{ FName(FString::Printf(TEXT(ErrorMsg), IsValid(Object) ? *Object->GetName() : *FString("nullptr"))) }; \
return Instance;

const FSFConditionalAnswer& SF::Conditional::Answer::Error::InvalidTestObject()
{
	SF_CONDITIONAL_IMPL_ERROR("Invalid test object");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::NumChildrenUnsupported()
{
	SF_CONDITIONAL_IMPL_ERROR("Number of children is not supported");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::HasInvalidChild()
{
	SF_CONDITIONAL_IMPL_ERROR("Has invalid child");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::HasChildWithRuntimeError()
{
	SF_CONDITIONAL_IMPL_ERROR("Has child with runtime error");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::NoPlayerController(const UWorld* World)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not find valid player controller in %s", World);
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::NoViewport(const APlayerController* Pc)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not find valid viewport for %s", Pc);
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoActor(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve instigator to supported class AActor: %s", TestObject);
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoActorComponent(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve instigator to supported class UActorComponent: %s", TestObject);
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoSceneComponent(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve instigator to supported class USceneComponent: %s", TestObject);
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoActorProvider(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve instigator to supported class UActorComponent: %s", TestObject);
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoTransformProvider(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve instigator to a FTransform: %s", TestObject);
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoActor(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve test object to supported class AActor: %s", TestObject);
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoActorComponent(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve test object to supported class UActorComponent: %s", TestObject);
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoSceneComponent(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve test object to supported class USceneComponent: %s", TestObject);
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoActorProvider(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve test object to supported class AActor or UActorComponent: %s", TestObject);
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoTransformProvider(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve test object to a FTransform: %s", TestObject);
}

#undef SF_CONDITIONAL_IMPL_ERROR
