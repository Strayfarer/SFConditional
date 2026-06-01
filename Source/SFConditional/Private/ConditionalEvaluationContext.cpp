// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalEvaluationContext.h"

#include "ConditionalLog.h"

UWorld* SF::FConditionalEvaluationContext::GetWorld() const
{
	if (TestObject)
		return TestObject->GetWorld();
	if (Instigator)
		return Instigator->GetWorld();
	return nullptr;
}

AActor* SF::FConditionalEvaluationContext::TryGetTestObjectActor() const
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

AController* SF::FConditionalEvaluationContext::TryGetTestObjectController() const
{
	if (const APawn* AsPawn = Cast<APawn>(TryGetTestObjectActor()))
		return AsPawn->GetController();
	if (AController* AsController = Cast<AController>(TryGetTestObjectActor()))
		return AsController;
	return nullptr;
}

APlayerController* SF::FConditionalEvaluationContext::TryGetTestObjectPlayerController() const
{
	return Cast<APlayerController>(TryGetTestObjectController());
}

TOptional<FTransform> SF::FConditionalEvaluationContext::TryGetTestObjectTransform() const
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
		if (const AActor* Owner = ActorComponent->GetOwner())
		{
			return Owner->GetTransform();
		}
		UE_LOG(LogConditional, VeryVerbose, TEXT("Conditional evaluation context found ActorComponent with invalid Owner!"))
	}
	return {};
}

AActor* SF::FConditionalEvaluationContext::TryGetInstigatorActor() const
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

AController* SF::FConditionalEvaluationContext::TryGetInstigatorController() const
{
	if (const APawn* AsPawn = Cast<APawn>(TryGetInstigatorActor()))
		return AsPawn->GetController();
	if (AController* AsController = Cast<AController>(TryGetInstigatorActor()))
		return AsController;
	return nullptr;
}

APlayerController* SF::FConditionalEvaluationContext::TryGetInstigatorPlayerController() const
{
	return Cast<APlayerController>(TryGetInstigatorController());
}

TOptional<FTransform> SF::FConditionalEvaluationContext::TryGetInstigatorTransform() const
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
		if (const AActor* Owner = ActorComponent->GetOwner())
		{
			return Owner->GetTransform();
		}
		UE_LOG(LogConditional, VeryVerbose, TEXT("Conditional evaluation context found ActorComponent with invalid Owner!"))
	}
	return {};
}
