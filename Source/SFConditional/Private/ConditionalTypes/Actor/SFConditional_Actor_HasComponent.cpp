// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Actor/SFConditional_Actor_HasComponent.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#if WITH_EDITOR
EDataValidationResult USFConditional_Actor_HasComponent::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);
	if (!ComponentClass)
	{
		Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
		Context.AddError(FText::FromString(FString::Printf(TEXT("ComponentClass is invalid for %s"), *GetPathNamePrettified())));
	}
	return Result;
}
#endif

FSFConditionalAnswer USFConditional_Actor_HasComponent::EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	if (const AActor* Actor = EvaluationContext.TryGetTestObjectActor())
	{
		TSet<UActorComponent*> Components = Actor->GetComponents();
		UActorComponent** Result = Algo::FindByPredicate(Components, [this](const UActorComponent* Component)
		{
			return Component->IsA(ComponentClass);
		});
		return Answer::FromBool(Result != nullptr);
	}
	return Answer::Error::TestObject::NoActorProvider(EvaluationContext.GetTestObject());
}

FString USFConditional_Actor_HasComponent::CreateConfigurationDebugString_Implementation() const
{
	return ComponentClass ? ComponentClass->GetName() : "No component class specified!";
}
