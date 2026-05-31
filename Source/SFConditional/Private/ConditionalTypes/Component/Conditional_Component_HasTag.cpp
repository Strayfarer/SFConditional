// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Component/Conditional_Component_HasTag.h"

#include "Algo/AllOf.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#if WITH_EDITOR
EDataValidationResult SF::UConditional_Component_HasTag::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);
	if (Tags.IsEmpty())
	{
		Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
		Context.AddWarning(FText::FromString(FString::Printf(TEXT("Tags is empty %s"), *GetPathNamePrettified())));
	}
	return Result;
}
#endif

SF::FConditionalAnswer SF::UConditional_Component_HasTag::EvaluateInternal_Implementation(
	const FConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	
	const auto* TestedActorComponent = Cast<UActorComponent>(EvaluationContext.GetTestObject());
	if (!TestedActorComponent)
	{
		return Answer::Error::TestObject::NoActorComponent(EvaluationContext.GetTestObject());
	}
	
	const bool bActorHasAllTags = Algo::AllOf(Tags, [TestedActorComponent](const FName& Tag)
		{
			return TestedActorComponent->ComponentHasTag(Tag);
		});
	return Answer::FromBool(bActorHasAllTags);
}

FString SF::UConditional_Component_HasTag::CreateConfigurationDebugString_Implementation() const
{
	TArray<FString> TagsAsStrings;
	Algo::Transform(Tags, TagsAsStrings, [](const FName& Tag){ return Tag.ToString(); });
	return FString::Join(TagsAsStrings, TEXT(", "));
}
