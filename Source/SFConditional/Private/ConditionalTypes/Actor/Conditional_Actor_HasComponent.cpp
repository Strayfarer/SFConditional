// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Actor/Conditional_Actor_HasComponent.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#if WITH_EDITOR
EDataValidationResult SF::UConditional_Actor_HasComponent::IsDataValid(class FDataValidationContext& Context) const
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

SF::FConditionalAnswer SF::UConditional_Actor_HasComponent::EvaluateInternal_Implementation(const FConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	
	if (!ComponentClass)
	{
		return Answer::Error::NoComponentClassSet();
	}
	
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

FString SF::UConditional_Actor_HasComponent::CreateConfigurationDebugString_Implementation() const
{
	return ComponentClass ? ComponentClass->GetName() : "";
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::NoComponentClassSet()
{
	static FConditionalAnswer Answer = FromErrorMsg(FString("No ComponentClass configured!"));
	return Answer;
}
