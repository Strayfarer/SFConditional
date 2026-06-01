// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Spatial/Conditional_Spatial_ScreenBox.h"

#include "Engine/Canvas.h"

SF::FConditionalAnswer SF::UConditional_Spatial_ScreenBox::EvaluateInternal_Implementation(
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

	// Compute box bounds
	float BoxMinX, BoxMaxX, BoxMinY, BoxMaxY;
	if (bFromCenterInsteadOfBorder)
	{
		BoxMinX = ViewportCenter.X - LeftDistance;
		BoxMaxX = ViewportCenter.X + RightDistance;
		BoxMinY = ViewportCenter.Y - TopDistance;
		BoxMaxY = ViewportCenter.Y + BottomDistance;
	}
	else
	{
		BoxMinX = 0.f + LeftDistance;
		BoxMaxX = ViewportSizeX - RightDistance;
		BoxMinY = 0.f + TopDistance;
		BoxMaxY = ViewportSizeY - BottomDistance;
	}

	// Binary answer is whether the tested location is inside the box
	const bool bBinaryAnswer =
		TestedScreenLoc.X >= BoxMinX && TestedScreenLoc.X <= BoxMaxX &&
		TestedScreenLoc.Y >= BoxMinY && TestedScreenLoc.Y <= BoxMaxY;

	// Fuzzy answer is 1 at center, 0 at furthest point on box and beyond
	const float DistTestedLocToCenter = FVector2D::Distance(TestedScreenLoc, ViewportCenter);
	float DistMaxToBoxBorder;
	if (bFromCenterInsteadOfBorder)
	{
		DistMaxToBoxBorder = FVector2D(
			FMath::Max(LeftDistance, RightDistance),
			FMath::Max(TopDistance, BottomDistance)
		).Size();
	}
	else
	{
		DistMaxToBoxBorder = FVector2D(
			FMath::Max(ViewportCenter.X - LeftDistance, ViewportCenter.X - RightDistance),
			FMath::Max(ViewportCenter.Y - TopDistance, ViewportCenter.Y - BottomDistance)
		).Size();
	}
	const float FuzzyAnswer = DistMaxToBoxBorder == 0.f 
		? 0.f
		: FMath::Clamp(1.f - (DistTestedLocToCenter / DistMaxToBoxBorder), 0.f, 1.f);

	return FConditionalAnswer{bBinaryAnswer, FuzzyAnswer};
}

FString SF::UConditional_Spatial_ScreenBox::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT("T:%.0f, R:%.0f, B:%.0f, L:%.0f"), 
		TopDistance, RightDistance, BottomDistance, LeftDistance);
}

#if WITH_GAMEPLAY_DEBUGGER
void SF::UConditional_Spatial_ScreenBox::VisualizeWithGameplayDebugger(FGameplayDebuggerCategory& Debugger, FGameplayDebuggerCanvasContext& Canvas)
{
	Super::VisualizeWithGameplayDebugger(Debugger, Canvas);

	const APlayerController* Pc = EvaluationContext.TryGetInstigatorPlayerController();
	if (!Pc || !Pc->GetLocalPlayer()) return;

	int32 ViewportX, ViewportY;
	Pc->GetViewportSize(ViewportX, ViewportY);
	if (ViewportX <= 0 || ViewportY <= 0) return;

	const FVector2D Center(ViewportX * 0.5f, ViewportY * 0.5f);

	FVector2D TopLeft, TopRight, BottomLeft, BottomRight;
	if (bFromCenterInsteadOfBorder)
	{
		TopLeft = FVector2D(Center.X - LeftDistance, Center.Y - TopDistance);
		TopRight = FVector2D(Center.X + RightDistance, Center.Y - TopDistance);
		BottomLeft = FVector2D(Center.X - LeftDistance, Center.Y + BottomDistance);
		BottomRight = FVector2D(Center.X + RightDistance, Center.Y + BottomDistance);
	}
	else
	{
		TopLeft = FVector2D(LeftDistance, TopDistance);
		TopRight = FVector2D(ViewportX - RightDistance, TopDistance);
		BottomLeft = FVector2D(LeftDistance, ViewportY - BottomDistance);
		BottomRight = FVector2D(ViewportX - RightDistance, ViewportY - BottomDistance);
	}

	Canvas.Canvas->K2_DrawLine(TopLeft, TopRight, 1.f, FLinearColor::Blue);
	Canvas.Canvas->K2_DrawLine(TopLeft, BottomLeft, 1.f, FLinearColor::Blue);
	Canvas.Canvas->K2_DrawLine(BottomRight, TopRight, 1.f, FLinearColor::Blue);
	Canvas.Canvas->K2_DrawLine(BottomRight, BottomLeft, 1.f, FLinearColor::Blue);
}
#endif // WITH_GAMEPLAY_DEBUGGER
