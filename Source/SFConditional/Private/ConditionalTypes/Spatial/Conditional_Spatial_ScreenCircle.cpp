// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Spatial/Conditional_Spatial_ScreenCircle.h"

SF::FConditionalAnswer SF::UConditional_Spatial_ScreenCircle::EvaluateInternal_Implementation(
	const FConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	
	const APlayerController* Pc = EvaluationContext.TryGetInstigatorPlayerController();
	if (!Pc || !Pc->GetLocalPlayer())
	{
		return Answer::Error::NoPlayerController(EvaluationContext.GetWorld());
	}

	int32 ViewportSizeX, ViewportSizeY;
	Pc->GetViewportSize(ViewportSizeX, ViewportSizeY);
	if (ViewportSizeX <= 0 || ViewportSizeY <= 0)
	{
		return Answer::Error::NoViewport(Pc);
	}

	const TOptional<FTransform> TestedWorldTransform = EvaluationContext.TryGetTestObjectTransform();
	if (!TestedWorldTransform.IsSet())
	{
		return Answer::Error::TestObject::NoTransformProvider(EvaluationContext.GetTestObject());
	}

	// Project world location to screen space
	FVector2D TestedScreenLoc;
	if (!Pc->ProjectWorldLocationToScreen(TestedWorldTransform->GetLocation(), TestedScreenLoc))
	{
		return Answer::No();
	}

	const FVector2D ViewportCenter = FVector2D(ViewportSizeX * 0.5f, ViewportSizeY * 0.5f);
	const FVector2D CircleCenter = ViewportCenter + FVector2D(OffsetHorizontal, OffsetVertical);

	const float DistTestedLocToCenter = FVector2D::Distance(TestedScreenLoc, CircleCenter);
	
	// Binary answer is whether the tested location is inside the circle
	const bool bBinaryAnswer = DistTestedLocToCenter <= Radius;

	// Fuzzy answer is 1 at center, 0 at furthest point on box and beyond
	const float FuzzyAnswer = Radius == 0.f 
		? 0.f
		: FMath::Clamp(1.f - (DistTestedLocToCenter / Radius), 0.f, 1.f);

	return FConditionalAnswer{bBinaryAnswer, FuzzyAnswer};
}

FString SF::UConditional_Spatial_ScreenCircle::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT("R:%.0f, Offset[%.0f,%.0f]"), 
		Radius, OffsetHorizontal, OffsetVertical);
}

#if WITH_GAMEPLAY_DEBUGGER
void SF::UConditional_Spatial_ScreenCircle::VisualizeWithGameplayDebugger(
	const FConditionalEvaluationContext& EvaluationContext, FGameplayDebuggerCategory& Debugger, FGameplayDebuggerCanvasContext& Canvas)
{
	Super::VisualizeWithGameplayDebugger(EvaluationContext, Debugger, Canvas);
	
	const APlayerController* Pc = EvaluationContext.TryGetInstigatorPlayerController();
	if (!Pc || !Pc->GetLocalPlayer()) return;

	int32 ViewportX, ViewportY;
	Pc->GetViewportSize(ViewportX, ViewportY);
	if (ViewportX <= 0 || ViewportY <= 0) return;

	const FVector2D ViewportCenter(ViewportX * 0.5f, ViewportY * 0.5f);
	const FVector2D CircleCenter = ViewportCenter + FVector2D(OffsetHorizontal, OffsetVertical);
	
	DrawDebugCanvas2DCircle(Canvas.Canvas.Get(), CircleCenter, Radius, 64, FColor::Yellow);
}
#endif
