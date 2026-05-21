// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalAnswer.h"

SF::FConditionalAnswer::FConditionalAnswer(const bool bInBinaryAnswer, const float InFuzzyAnswer)
	: bBinaryAnswer(bInBinaryAnswer), FuzzyAnswer(InFuzzyAnswer) {}

SF::FConditionalAnswer::FConditionalAnswer(const FString& InErrorMsg) 
	: ErrorMessage(InErrorMsg) {}

SF::FConditionalAnswer::FConditionalAnswer(const FName& InErrorMsg)
	: ErrorMessage(InErrorMsg) {}

bool SF::FConditionalAnswer::operator==(const FConditionalAnswer& Other) const
{
	if (!ErrorMessage.IsNone() || !Other.ErrorMessage.IsNone())
	{
		return ErrorMessage == Other.ErrorMessage;
	}
	return bBinaryAnswer == Other.bBinaryAnswer && FMath::IsNearlyEqual(FuzzyAnswer, Other.FuzzyAnswer);
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Yes()
{
    static FConditionalAnswer Instance(true, 1.f);
	return Instance;
}

const SF::FConditionalAnswer& SF::Conditional::Answer::No()
{
	static FConditionalAnswer Instance{ false, 0.f };
	return Instance;
}

SF::FConditionalAnswer SF::Conditional::Answer::Create(const bool bBinaryAnswer, const float FuzzyAnswer)
{
	return FConditionalAnswer(bBinaryAnswer, FuzzyAnswer);
}

SF::FConditionalAnswer SF::Conditional::Answer::FromBool(const bool bBooleanAnswer)
{
	return FConditionalAnswer(bBooleanAnswer, bBooleanAnswer ? 1.f : 0.f);
}

SF::FConditionalAnswer SF::Conditional::Answer::FromErrorMsg(const FString& InErrorMsg)
{
	return FConditionalAnswer(InErrorMsg);
}

SF::FConditionalAnswer SF::Conditional::Answer::FromErrorMsg(const FName& InErrorMsg)
{
	return FConditionalAnswer(InErrorMsg.ToString());
}

#define SF_CONDITIONAL_IMPL_ERROR(ErrorMsg) \
	static FConditionalAnswer Instance{ FName(ErrorMsg) }; \
return Instance;

#define SF_CONDITIONAL_IMPL_ERROR_OBJ(ErrorMsg, Object) \
	static FConditionalAnswer Instance{ FName(FString::Printf(TEXT(ErrorMsg), IsValid(Object) ? *Object->GetName() : *FString("nullptr"))) }; \
return Instance;

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::InvalidTestObject()
{
	SF_CONDITIONAL_IMPL_ERROR("Invalid test object");
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::NumChildrenUnsupported()
{
	SF_CONDITIONAL_IMPL_ERROR("Number of children is not supported");
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::HasInvalidChild()
{
	SF_CONDITIONAL_IMPL_ERROR("Has invalid child");
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::HasChildWithRuntimeError()
{
	SF_CONDITIONAL_IMPL_ERROR("Has child with runtime error");
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::NoPlayerController(const UWorld* World)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not find valid player controller in %s", World);
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::NoViewport(const APlayerController* Pc)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not find valid viewport for %s", Pc);
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoActor(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve instigator to supported class AActor: %s", TestObject);
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoActorComponent(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve instigator to supported class UActorComponent: %s", TestObject);
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoSceneComponent(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve instigator to supported class USceneComponent: %s", TestObject);
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoActorProvider(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve instigator to supported class UActorComponent: %s", TestObject);
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoTransformProvider(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve instigator to a FTransform: %s", TestObject);
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoActor(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve test object to supported class AActor: %s", TestObject);
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoActorComponent(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve test object to supported class UActorComponent: %s", TestObject);
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoSceneComponent(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve test object to supported class USceneComponent: %s", TestObject);
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoActorProvider(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve test object to supported class AActor or UActorComponent: %s", TestObject);
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoTransformProvider(const UObject* TestObject)
{
	SF_CONDITIONAL_IMPL_ERROR_OBJ("Could not resolve test object to a FTransform: %s", TestObject);
}

#undef SF_CONDITIONAL_IMPL_ERROR
