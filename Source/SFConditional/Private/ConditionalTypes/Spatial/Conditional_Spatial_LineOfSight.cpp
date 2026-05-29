// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Spatial/Conditional_Spatial_LineOfSight.h"

#include "Kismet/GameplayStatics.h"

SF::FConditionalAnswer SF::UConditional_Spatial_LineOfSight::EvaluateInternal_Implementation(
	const FConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	
	const TOptional<FTransform> InstigatorWorldTransform = EvaluationContext.TryGetInstigatorTransform();
	if (!InstigatorWorldTransform.IsSet())
	{
		return Answer::Error::Instigator::NoTransformProvider(EvaluationContext.GetInstigator());
	}
	
	const APlayerController* Pc = UGameplayStatics::GetPlayerController(EvaluationContext.GetWorld(), 0);
	if (!Pc || !Pc->GetLocalPlayer())
	{
		return Answer::Error::NoPlayerController(EvaluationContext.GetWorld());
	}

	const FVector CameraForward = Pc->GetControlRotation().Vector();
	const FVector TraceStart = InstigatorWorldTransform.GetValue().GetLocation();
	const FVector TraceEnd = TraceStart + MaxDistance * CameraForward;
	
	FCollisionQueryParams TraceParams;
	TraceParams.TraceTag = GetFName();
	if (bShouldIgnoreInstigator)
	{
		TraceParams.AddIgnoredSourceObject(EvaluationContext.GetInstigator());
	}
		
	FHitResult HitResult;
	const bool bDidHit = EvaluationContext.GetWorld()
		->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, CollisionChannelToCheck, TraceParams);
	return Answer::FromBool(bDidHit);
}

FString SF::UConditional_Spatial_LineOfSight::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT("MaxDistance %f"), MaxDistance);
}

#if WITH_GAMEPLAY_DEBUGGER
void SF::UConditional_Spatial_LineOfSight::VisualizeWithGameplayDebugger(FGameplayDebuggerCategory& Debugger,
	FGameplayDebuggerCanvasContext& Canvas)
{
	Super::VisualizeWithGameplayDebugger(Debugger, Canvas);

	const APlayerController* PC = Canvas.PlayerController.Get();
	if (!PC) return;
	
	const APawn* Pawn = PC->GetPawn();
	if (!Pawn) return;

	const FVector CameraForward = PC->GetControlRotation().Vector();
	const FVector StartLocation = Pawn->GetActorLocation();
	
	DrawDebugLine(PC->GetWorld(), StartLocation, StartLocation + MaxDistance * CameraForward, FColor::Yellow,
		false, -1, 0, 3);
}
#endif // WITH_GAMEPLAY_DEBUGGER
