// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Actor/SFConditional_Actor_IsTicking.h"

FSFConditionalAnswer USFConditional_Actor_IsTicking::EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	if (const AActor* Actor = EvaluationContext.TryGetTestObjectActor())
	{
		return Answer::FromBool(Actor->IsActorTickEnabled());
	}
	return Answer::Error::TestObject::NoActorProvider(EvaluationContext.GetTestObject());
}
