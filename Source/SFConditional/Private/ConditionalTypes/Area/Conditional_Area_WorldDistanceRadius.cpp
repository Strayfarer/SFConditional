// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Area/Conditional_Area_WorldDistanceRadius.h"

SF::FConditionalAnswer SF::UConditional_Area_WorldDistanceRadius::EvaluateInternal_Implementation(
	const FConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	
	const TOptional<FTransform> EvaluatedLocation = EvaluationContext.TryGetTestObjectTransform();
	if (!EvaluatedLocation.IsSet())
	{
		return Answer::Error::TestObject::NoTransformProvider(EvaluationContext.GetTestObject());
	}
	
	const TOptional<FTransform> InstigatorLocation = EvaluationContext.TryGetInstigatorTransform();
	if (!InstigatorLocation.IsSet())
	{
		return Answer::Error::Instigator::NoTransformProvider(EvaluationContext.GetInstigator());
	}
	
	const float Dist = FVector::Dist(
		InstigatorLocation.GetValue().GetLocation(),
		EvaluatedLocation.GetValue().GetLocation());

	const bool bBinaryAnswer = Dist <= Radius;
	const float FuzzyAnswer = bBinaryAnswer ? 1.f - Dist / Radius : 0.f;
	
	return { bBinaryAnswer, FuzzyAnswer };
}

FString SF::UConditional_Area_WorldDistanceRadius::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT("R:%.0f"), Radius);
}

#if WITH_GAMEPLAY_DEBUGGER
void SF::UConditional_Area_WorldDistanceRadius::VisualizeWithGameplayDebugger(FGameplayDebuggerCategory& Debugger,
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
