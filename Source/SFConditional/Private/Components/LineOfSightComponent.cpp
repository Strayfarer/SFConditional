// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "Components/LineOfSightComponent.h"

#include "Kismet/GameplayStatics.h"


SF::ULineOfSightComponent::ULineOfSightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void SF::ULineOfSightComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	const APlayerController* Pc = UGameplayStatics::GetPlayerController(this, 0);
	if (!IsValid(Pc) || !IsValid(GetOwner()))
		return;

	const FVector CameraForward = Pc->GetControlRotation().Vector();
	const FVector TraceStart = GetOwner()->GetActorLocation();
	const FVector TraceEnd = TraceStart + MaxDistance * CameraForward;
	
	TraceHandle = GetWorld()->AsyncLineTraceByChannel(
		EAsyncTraceType::Single,
		TraceStart, TraceEnd,
		CollisionChannelToCheck,
		TraceQueryParams,
		FCollisionResponseParams::DefaultResponseParam,
		&OnPendingTraceQueryProcessedDelegate);
}

float SF::ULineOfSightComponent::GetTraceDistance() const
{
	return MaxDistance;
}

const FHitResult& SF::ULineOfSightComponent::GetCurrentHitResult() const
{
	if (CurrentTraceDatum.IsSet())
	{
		if (!CurrentTraceDatum.GetValue().OutHits.IsEmpty())
		{
			return CurrentTraceDatum.GetValue().OutHits[0];
		}
	}
	static FHitResult EmptyResult{};
	return EmptyResult;
}

void SF::ULineOfSightComponent::BeginPlay()
{
	Super::BeginPlay();
	
	TraceQueryParams.TraceTag = GetFName();
	if (bShouldOwnerActor)
	{
		TraceQueryParams.AddIgnoredSourceObject(GetOwner());
	}
	
	OnPendingTraceQueryProcessedDelegate.BindUObject(this, &ThisClass::HandlePendingTraceQueryProcessed);
}

void SF::ULineOfSightComponent::HandlePendingTraceQueryProcessed(const FTraceHandle& InTraceHandle, FTraceDatum& InTraceDatum)
{
	CurrentTraceDatum = InTraceDatum;
}
