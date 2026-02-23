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

const FSFConditionalAnswer& SF::Conditional::Answer::Error::NoPlayerController()
{
	SF_CONDITIONAL_IMPL_ERROR("Could not find valid player controller");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::NoViewport()
{
	SF_CONDITIONAL_IMPL_ERROR("Could not find valid viewport");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoActor()
{
	SF_CONDITIONAL_IMPL_ERROR("Could not resolve instigator to supported class AActor");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoActorComponent()
{
	SF_CONDITIONAL_IMPL_ERROR("Could not resolve instigator to supported class UActorComponent");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoSceneComponent()
{
	SF_CONDITIONAL_IMPL_ERROR("Could not resolve instigator to supported class USceneComponent");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoActorProvider()
{
	SF_CONDITIONAL_IMPL_ERROR("Could not resolve instigator to supported class UActorComponent");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::Instigator::NoTransformProvider()
{
	SF_CONDITIONAL_IMPL_ERROR("Could not resolve instigator to a FTransform");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoActor()
{
	SF_CONDITIONAL_IMPL_ERROR("Could not resolve test object to supported class AActor");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoActorComponent()
{
	SF_CONDITIONAL_IMPL_ERROR("Could not resolve test object to supported class UActorComponent");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoSceneComponent()
{
	SF_CONDITIONAL_IMPL_ERROR("Could not resolve test object to supported class USceneComponent");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoActorProvider()
{
	SF_CONDITIONAL_IMPL_ERROR("Could not resolve test object to supported class AActor or UActorComponent");
}

const FSFConditionalAnswer& SF::Conditional::Answer::Error::TestObject::NoTransformProvider()
{
	SF_CONDITIONAL_IMPL_ERROR("Could not resolve test object to a FTransform");
}

#undef SF_CONDITIONAL_IMPL_ERROR
