// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "SFConditionalEvaluationContext.h"

AActor* FSFConditionalEvaluationContext::TryGetTestObjectActor() const
{
	if (AActor* Actor = Cast<AActor>(TestObject))
	{
		return Actor;
	}
	if (const UActorComponent* ActorComponent = Cast<UActorComponent>(TestObject))
	{
		return ActorComponent->GetOwner();
	}
	return nullptr;
}

TOptional<FTransform> FSFConditionalEvaluationContext::TryGetTestObjectTransform() const
{
	if (const AActor* Actor = TryGetTestObjectAs<AActor>())
	{
		return Actor->GetTransform();
	}
	if (const auto* SceneComponent = TryGetTestObjectAs<USceneComponent>())
	{
		return SceneComponent->GetComponentTransform();
	}
	if (const auto* ActorComponent = TryGetTestObjectAs<UActorComponent>())
	{
		return ActorComponent->GetOwner()->GetTransform();
	}
	return {};
}

AActor* FSFConditionalEvaluationContext::TryGetInstigatorActor() const
{
	if (AActor* Actor = Cast<AActor>(Instigator))
	{
		return Actor;
	}
	if (const UActorComponent* ActorComponent = Cast<UActorComponent>(Instigator))
	{
		return ActorComponent->GetOwner();
	}
	return nullptr;
}

TOptional<FTransform> FSFConditionalEvaluationContext::TryGetInstigatorTransform() const
{
	if (const auto* Actor = TryGetInstigatorAs<AActor>())
	{
		return Actor->GetTransform();
	}
	if (const auto* SceneComponent = TryGetInstigatorAs<USceneComponent>())
	{
		return SceneComponent->GetComponentTransform();
	}
	if (const auto* ActorComponent = TryGetInstigatorAs<UActorComponent>())
	{
		return ActorComponent->GetOwner()->GetTransform();
	}
	return {};
}
