// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Area/SFConditional_Area_ScreenBox.h"

#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"

FSFConditionalAnswer USFConditional_Area_ScreenBox::EvaluateInternal_Implementation(
	const FSFConditionalEvaluationContext& EvaluationContext)
{
	const APlayerController* Pc = UGameplayStatics::GetPlayerController(EvaluationContext.GetWorld(), 0);
	if (!Pc || !Pc->GetLocalPlayer())
	{
		return SF::Conditional::Answer::Error::NoPlayerController();
	}

	// Get screen size
	int32 ViewportX, ViewportY;
	Pc->GetViewportSize(ViewportX, ViewportY);
	if (ViewportX <= 0 || ViewportY <= 0)
	{
		return SF::Conditional::Answer::Error::NoViewport();
	}

	const TOptional<FTransform> EvaluatedTransform = EvaluationContext.TryGetTestObjectTransform();
	if (!EvaluatedTransform.IsSet())
	{
		return SF::Conditional::Answer::Error::TestObject::NoTransformProvider();
	}

	// Project world location to screen space. If we're outside screen space, return No.
	FVector2D ScreenPosition;
	if (!Pc->ProjectWorldLocationToScreen(EvaluatedTransform->GetLocation(), ScreenPosition))
	{
		return SF::Conditional::Answer::No();
	}

	const FVector2D ScreenCenter = FVector2D(ViewportX * 0.5f, ViewportY * 0.5f);

	// Define box bounds
	float MinX, MaxX, MinY, MaxY;
	if (bFromCenterInsteadOfBorder)
	{
		MinX = ScreenCenter.X - LeftDistance;
		MaxX = ScreenCenter.X + RightDistance;
		MinY = ScreenCenter.Y - TopDistance;
		MaxY = ScreenCenter.Y + BottomDistance;
	}
	else
	{
		MinX = LeftDistance;
		MaxX = ViewportX - RightDistance;
		MinY = TopDistance;
		MaxY = ViewportY - BottomDistance;
	}

	// Check containment
	const bool bInside =
		ScreenPosition.X >= MinX && ScreenPosition.X <= MaxX &&
		ScreenPosition.Y >= MinY && ScreenPosition.Y <= MaxY;

	// Fuzzy score: 1 at center, 0 at furthest edge
	const float DistanceToCenter = FVector2D::Distance(ScreenPosition, ScreenCenter);
	float MaxDistance;
	if (bFromCenterInsteadOfBorder)
	{
		MaxDistance = FVector2D(
			FMath::Max(LeftDistance, RightDistance),
			FMath::Max(TopDistance, BottomDistance)
		).Size();
	}
	else
	{
		MaxDistance = FVector2D(
			FMath::Max(ScreenCenter.X - LeftDistance, ScreenCenter.X - RightDistance),
			FMath::Max(ScreenCenter.Y - TopDistance, ScreenCenter.Y - BottomDistance)
		).Size();
	}
	const float FuzzyScore = FMath::Clamp(1.0f - (DistanceToCenter / MaxDistance), 0.f, 1.f);

	return FSFConditionalAnswer(bInside, FuzzyScore);
}

FString USFConditional_Area_ScreenBox::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT("T:%.0f, R:%.0f, B:%.0f, L:%.0f"), 
		TopDistance, RightDistance, BottomDistance, LeftDistance);
}

#if WITH_GAMEPLAY_DEBUGGER
void USFConditional_Area_ScreenBox::VisualizeWithGameplayDebugger(FGameplayDebuggerCategory& Debugger, FGameplayDebuggerCanvasContext& Canvas)
{
	Super::VisualizeWithGameplayDebugger(Debugger, Canvas);

	const APlayerController* PC = Canvas.PlayerController.Get();
	if (!PC) return;

	int32 ViewportX, ViewportY;
	PC->GetViewportSize(ViewportX, ViewportY);
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

	Canvas.Canvas->K2_DrawBox(Center - FVector2D(2), FVector2D(4), 1.f, FColor::Blue);
}
#endif // WITH_GAMEPLAY_DEBUGGER
