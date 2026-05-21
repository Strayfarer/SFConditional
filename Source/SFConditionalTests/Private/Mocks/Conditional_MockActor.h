// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Conditional_MockActor.generated.h"

/**
 * Mock actor used for testing.
 */
UCLASS(NotBlueprintType, Hidden)
class AConditional_MockActor : public AActor
{
	GENERATED_BODY()
	
	AConditional_MockActor();
	
	UPROPERTY()
	TObjectPtr<USceneComponent> SceneComponent = nullptr;
};
