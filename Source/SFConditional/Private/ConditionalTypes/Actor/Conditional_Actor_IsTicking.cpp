// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Actor/Conditional_Actor_IsTicking.h"

SF::FConditionalAnswer SF::UConditional_Actor_IsTicking::EvaluateInternal_Implementation(const FConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	if (const AActor* Actor = EvaluationContext.TryGetTestObjectActor())
	{
		return Answer::FromBool(Actor->IsActorTickEnabled());
	}
	return Answer::Error::TestObject::NoActorProvider(EvaluationContext.GetTestObject());
}
