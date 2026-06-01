// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Spatial/Conditional_Spatial_WorldSphere.h"

SF::FConditionalAnswer SF::UConditional_Spatial_WorldSphere::EvaluateInternal_Implementation(
	const FConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	
	const TOptional<FTransform> TestLocation = EvaluationContext.TryGetTestObjectTransform();
	if (!TestLocation.IsSet())
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
		TestLocation.GetValue().GetLocation());

	const bool bBinaryAnswer = Dist <= Radius;
	
	float FuzzyAnswer = 0.f;
	if      (!bBinaryAnswer) { FuzzyAnswer = 0.f; }
	else if (Radius > 0.f)   { FuzzyAnswer = 1.f - Dist / Radius; }
	else if (Radius == 0.f)  { FuzzyAnswer = 1.f; }
	
	return { bBinaryAnswer, FuzzyAnswer };
}

FString SF::UConditional_Spatial_WorldSphere::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT("R:%.0f"), Radius);
}

#if WITH_GAMEPLAY_DEBUGGER
void SF::UConditional_Spatial_WorldSphere::VisualizeWithGameplayDebugger(
	const FConditionalEvaluationContext& EvaluationContext, FGameplayDebuggerCategory& Debugger, FGameplayDebuggerCanvasContext& Canvas)
{
	Super::VisualizeWithGameplayDebugger(EvaluationContext, Debugger, Canvas);
	
	const TOptional<FTransform> InstigatorTransform = EvaluationContext.TryGetInstigatorTransform();
	if (!InstigatorTransform.IsSet())
		return;
	
	DrawDebugSphere(EvaluationContext.GetWorld(), InstigatorTransform.GetValue().GetLocation(), Radius, 64, FColor::Orange);
}
#endif // WITH_GAMEPLAY_DEBUGGER
