// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Actor/Conditional_Actor_HasTag.h"

#include "Algo/AllOf.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#if WITH_EDITOR
EDataValidationResult SF::UConditional_Actor_HasTag::IsDataValid(class FDataValidationContext& Context) const
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

SF::FConditionalAnswer SF::UConditional_Actor_HasTag::EvaluateInternal_Implementation(
	const FConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	
	const AActor* TestedActor = EvaluationContext.TryGetTestObjectActor();
	if (!TestedActor)
	{
		return Answer::Error::TestObject::NoActorProvider(EvaluationContext.GetTestObject());
	}
	
	const bool bActorHasAllTags = Algo::AllOf(Tags, [TestedActor](const FName& Tag)
		{
			return TestedActor->ActorHasTag(Tag);
		});
	return Answer::FromBool(bActorHasAllTags);
}

FString SF::UConditional_Actor_HasTag::CreateConfigurationDebugString_Implementation() const
{
	TArray<FString> TagsAsStrings;
	Algo::Transform(Tags, TagsAsStrings, [](const FName& Tag){ return Tag.ToString(); });
	return FString::Join(TagsAsStrings, TEXT(", "));
}
