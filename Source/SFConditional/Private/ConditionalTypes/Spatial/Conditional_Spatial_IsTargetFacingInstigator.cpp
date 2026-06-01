// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Spatial/Conditional_Spatial_IsTargetFacingInstigator.h"

SF::FConditionalAnswer SF::UConditional_Spatial_IsTargetFacingInstigator::EvaluateInternal_Implementation(
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

FString SF::UConditional_Spatial_IsTargetFacingInstigator::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT("MaxAngle: %.0f°"), MaxAngle);
}
