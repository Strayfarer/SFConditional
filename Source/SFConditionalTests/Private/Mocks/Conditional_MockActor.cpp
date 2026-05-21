// Copyright Strayfarer & Contributors. Released under the MIT license.

#include "Conditional_MockActor.h"

AConditional_MockActor::AConditional_MockActor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
}
