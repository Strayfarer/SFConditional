// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Spatial/Conditional_Spatial_IsTestObjectFacingInstigator.h"

SF::FConditionalAnswer SF::UConditional_Spatial_IsTestObjectFacingInstigator::EvaluateInternal_Implementation(
	const FConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	
	const TOptional<FTransform> TestTransform = EvaluationContext.TryGetTestObjectTransform();
	if (!TestTransform.IsSet())
	{
		return Answer::Error::TestObject::NoTransformProvider(EvaluationContext.GetTestObject());
	}
	
	const TOptional<FTransform> InstigatorTransform = EvaluationContext.TryGetInstigatorTransform();
	if (!InstigatorTransform.IsSet())
	{
		return Answer::Error::Instigator::NoTransformProvider(EvaluationContext.GetInstigator());
	}
	
	const FVector OptimalTargetForward = InstigatorTransform.GetValue().GetLocation() - TestTransform.GetValue().GetLocation();
	const FVector ActualTargetForward = InstigatorTransform.GetValue().Rotator().Vector();
	const float Angle = ActualTargetForward.CosineAngle2D(OptimalTargetForward);
	const float NormalizedAngle = (Angle + 1.f) / 2.f;
	const float DegreesAngle = NormalizedAngle * 180.f;

	const bool bBinaryAnswer = DegreesAngle <= MaxAngle / 2.f;
	
	float FuzzyAnswer = 0.f;
	if      (!bBinaryAnswer)  { FuzzyAnswer = 0.f; }
	else if (MaxAngle > 0.f)  { FuzzyAnswer = 1.f - DegreesAngle / MaxAngle; }
	else if (MaxAngle == 0.f) { FuzzyAnswer = 0.f; }
	
	return { bBinaryAnswer, FuzzyAnswer };
}

FString SF::UConditional_Spatial_IsTestObjectFacingInstigator::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT("MaxAngle: %.0f°"), MaxAngle);
}

#if WITH_GAMEPLAY_DEBUGGER
void SF::UConditional_Spatial_IsTestObjectFacingInstigator::VisualizeTestObjectWithGameplayDebugger(
	const FConditionalEvaluationContext& EvaluationContext, FGameplayDebuggerCategory& Debugger,
	FGameplayDebuggerCanvasContext& Canvas)
{
	Super::VisualizeTestObjectWithGameplayDebugger(EvaluationContext, Debugger, Canvas);

	const TOptional<FTransform> TestTransform = EvaluationContext.TryGetTestObjectTransform();
	if (!TestTransform.IsSet())
		return;
	
	const TOptional<FTransform> InstigatorTransform = EvaluationContext.TryGetInstigatorTransform();
	if (!InstigatorTransform.IsSet())
		return;
	
	const FVector TargetToInstigator = InstigatorTransform.GetValue().GetLocation() - TestTransform.GetValue().GetLocation();
	const FVector TargetForward = InstigatorTransform.GetValue().Rotator().Vector();
	const float Angle = TargetForward.CosineAngle2D(TargetToInstigator);
	const float NormalizedAngle = (Angle + 1.f) / 2.f;
	const float DegreesAngle = NormalizedAngle * 180.f;
	const bool bBinaryAnswer = DegreesAngle <= MaxAngle / 2.f;
	
	const FVector Left = TargetForward.GetSafeNormal2D().RotateAngleAxis(MaxAngle, FVector::UpVector);
	const FVector Right = TargetForward.GetSafeNormal2D().RotateAngleAxis(-MaxAngle, FVector::UpVector);
	
	const FColor Color = bBinaryAnswer ? FColor::Green : FColor::Cyan;
	DrawDebugCircleArc(EvaluationContext.GetWorld(), TestTransform.GetValue().GetLocation(), 200.f, -TargetForward.GetSafeNormal2D(), FMath::DegreesToRadians(MaxAngle), 32, Color);
	DrawDebugLine(EvaluationContext.GetWorld(), TestTransform.GetValue().GetLocation(), TestTransform.GetValue().GetLocation() - TargetForward.GetSafeNormal2D() * 200.f, Color);
	DrawDebugLine(EvaluationContext.GetWorld(), TestTransform.GetValue().GetLocation(), TestTransform.GetValue().GetLocation() - Left.GetSafeNormal2D() * 200.f, Color);
	DrawDebugLine(EvaluationContext.GetWorld(), TestTransform.GetValue().GetLocation(), TestTransform.GetValue().GetLocation() - Right.GetSafeNormal2D() * 200.f, Color);
	DrawDebugLine(EvaluationContext.GetWorld(), TestTransform.GetValue().GetLocation(), TestTransform.GetValue().GetLocation() + TargetToInstigator.GetSafeNormal2D()  * 200.f, FColor::Black, false, -1, 0, 2.f);
}
#endif
