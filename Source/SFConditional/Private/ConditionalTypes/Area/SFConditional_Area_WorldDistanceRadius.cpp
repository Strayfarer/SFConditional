// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Area/SFConditional_Area_WorldDistanceRadius.h"

FSFConditionalAnswer USFConditional_Area_WorldDistanceRadius::EvaluateInternal_Implementation(
	const FSFConditionalEvaluationContext& EvaluationContext)
{
	const TOptional<FTransform> EvaluatedLocation = EvaluationContext.TryGetTestObjectTransform();
	if (!EvaluatedLocation.IsSet())
	{
		return SF::Conditional::Answer::Error::TestObject::NoTransformProvider();
	}
	
	const TOptional<FTransform> InstigatorLocation = EvaluationContext.TryGetInstigatorTransform();
	if (!InstigatorLocation.IsSet())
	{
		return SF::Conditional::Answer::Error::Instigator::NoTransformProvider();
	}
	
	const float Dist = FVector::Dist(
		InstigatorLocation.GetValue().GetLocation(),
		EvaluatedLocation.GetValue().GetLocation());

	const bool bBinaryAnswer = Dist <= Radius;
	const float FuzzyAnswer = bBinaryAnswer ? 1.f - Dist / Radius : 0.f;
	
	return { bBinaryAnswer, FuzzyAnswer };
}

FString USFConditional_Area_WorldDistanceRadius::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT("R:%.0f"), Radius);
}

#if WITH_GAMEPLAY_DEBUGGER
void USFConditional_Area_WorldDistanceRadius::VisualizeWithGameplayDebugger(FGameplayDebuggerCategory& Debugger,
	FGameplayDebuggerCanvasContext& Canvas)
{
	Super::VisualizeWithGameplayDebugger(Debugger, Canvas);

	const APlayerController* PC = Canvas.PlayerController.Get();
	if (!PC) return;

	const APawn* Pawn = PC->GetPawn();
	if (!Pawn) return;

	Debugger.AddShape(FGameplayDebuggerShape::MakeCapsule(Pawn->GetActorLocation(), Radius, 25.f, FColor::Red));
	Debugger.AddShape(FGameplayDebuggerShape::MakeCylinder(Pawn->GetActorLocation(), Radius, 25.f, FColor::Orange));
}
#endif // WITH_GAMEPLAY_DEBUGGER
