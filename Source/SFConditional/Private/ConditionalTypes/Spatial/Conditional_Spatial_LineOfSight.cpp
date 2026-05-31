// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Spatial/Conditional_Spatial_LineOfSight.h"

#include "Components/LineOfSightComponent.h"

SF::FConditionalAnswer SF::UConditional_Spatial_LineOfSight::EvaluateInternal_Implementation(
	const FConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	
	auto* LineOfSightComponent = EvaluationContext.TryGetInstigatorActorComponent<ULineOfSightComponent>();
	if (!LineOfSightComponent)
		return Answer::Error::NoLineOfSightComponentAvailable();
	
	const FHitResult HitResult = LineOfSightComponent->GetCurrentHitResult();
	if (!HitResult.bBlockingHit)
		return Answer::No();
	
	if (HitResult.Component != EvaluationContext.GetTestObject() 
		&& HitResult.GetActor() != EvaluationContext.TryGetTestObjectActor()
		&& !HitResult.GetActor()->GetComponents().Contains(EvaluationContext.TryGetTestObjectActorComponent<UActorComponent>()))
	{
		return Answer::No();
	}
	
	return Answer::Create(true, 1.f - HitResult.Distance / LineOfSightComponent->GetTraceDistance());
}

FString SF::UConditional_Spatial_LineOfSight::CreateConfigurationDebugString_Implementation() const
{
	return FString::Printf(TEXT(""));
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

	const auto* LineOfSightComponent = Pawn->GetComponentByClass<ULineOfSightComponent>();
	if (!LineOfSightComponent) return;
	
	const FVector CameraForward = PC->GetControlRotation().Vector();
	const FVector StartLocation = Pawn->GetActorLocation();
	
	const FHitResult& HitResult = LineOfSightComponent->GetCurrentHitResult();
	
	DrawDebugLine(PC->GetWorld(), 
		StartLocation + CameraForward * FMath::Min(35.f, LineOfSightComponent->GetTraceDistance()),
		StartLocation + CameraForward * LineOfSightComponent->GetTraceDistance(), 
		HitResult.bBlockingHit ? FColor(0.f,255.f,0.f) : FColor(255.f,255.f,0.f),
		false, -1, 0, 1);
}
#endif // WITH_GAMEPLAY_DEBUGGER

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::NoLineOfSightComponentAvailable()
{
	static FConditionalAnswer Answer = FromErrorMsg(FString("No LineOfSightComponent could be found on the instigator!"));
	return Answer;
}
