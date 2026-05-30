// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LineOfSightComponent.generated.h"


namespace SF
{
	UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
	class SFCONDITIONAL_API ULineOfSightComponent : public UActorComponent
	{
		GENERATED_BODY()

	public:
		ULineOfSightComponent();

		// UActorComponent
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		// --
		
		UFUNCTION(BlueprintPure)
		float GetTraceDistance() const;
		
		UFUNCTION(BlueprintPure)
		const FHitResult& GetCurrentHitResult() const;
		
	protected:
		// UActorComponent
		virtual void BeginPlay() override;
		// --
		
		void HandlePendingTraceQueryProcessed(const FTraceHandle& InTraceHandle, FTraceDatum& InTraceDatum);
		
		UPROPERTY(EditAnywhere)
		float MaxDistance = 200.f;
		
		UPROPERTY(EditAnywhere)
		TEnumAsByte<ECollisionChannel> CollisionChannelToCheck = ECC_Visibility;
		
		UPROPERTY(EditAnywhere)
		bool bShouldOwnerActor = true;
		
		FCollisionQueryParams TraceQueryParams{};
		FTraceHandle TraceHandle{};
		FTraceDelegate OnPendingTraceQueryProcessedDelegate{};
		TOptional<FTraceDatum> CurrentTraceDatum{};
	};
}
