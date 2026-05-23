// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Object/Conditional_Object_IsOfClass.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#if WITH_EDITOR
EDataValidationResult SF::UConditional_Object_IsOfClass::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);
	if (bPreloadClassToCheckFor & !PreLoadedClassToCheckFor)
	{
		Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
		Context.AddError(FText::FromString(FString::Printf(TEXT("PreLoadedClassToCheckFor is invalid for %s"), *GetPathNamePrettified())));
	}
	if (!bPreloadClassToCheckFor & !SyncLoadedClassToCheckFor.ToSoftObjectPath().IsValid())
	{
		Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
		Context.AddError(FText::FromString(FString::Printf(TEXT("SyncLoadedClassToCheckFor is invalid for %s"), *GetPathNamePrettified())));
	}
	return Result;
}

void SF::UConditional_Object_IsOfClass::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (bPreloadClassToCheckFor)
	{
		if (SyncLoadedClassToCheckFor.ToSoftObjectPath().IsValid() && !PreLoadedClassToCheckFor)
		{
			PreLoadedClassToCheckFor = TSubclassOf<UObject>(SyncLoadedClassToCheckFor.LoadSynchronous());
		}
		SyncLoadedClassToCheckFor = nullptr;
	}
	else
	{
		if (!SyncLoadedClassToCheckFor.ToSoftObjectPath().IsValid() && PreLoadedClassToCheckFor)
		{
			SyncLoadedClassToCheckFor = PreLoadedClassToCheckFor;
		}
		PreLoadedClassToCheckFor = nullptr;
	}
}
#endif

SF::FConditionalAnswer SF::UConditional_Object_IsOfClass::EvaluateInternal_Implementation(const FConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	
	UClass* ClassToCheckFor = ResolveClassToCheckFor();
	if (!ClassToCheckFor)
	{
		return Answer::Error::NoClassToCheckForSpecified();
	}
	
	if (bTryTestAssociatedActor)
	{
		if (const AActor* Actor = EvaluationContext.TryGetTestObjectActor())
		{
			return Answer::FromBool(Actor->IsA(ClassToCheckFor));
		}
	}
	return Answer::FromBool(EvaluationContext.GetTestObject()->IsA(ClassToCheckFor));
}

FString SF::UConditional_Object_IsOfClass::CreateConfigurationDebugString_Implementation() const
{
	FString ClassName{};
	if (bPreloadClassToCheckFor)
	{
		ClassName = IsValid(PreLoadedClassToCheckFor) ? PreLoadedClassToCheckFor->GetName() : "";
	}
	else
	{
		ClassName = SyncLoadedClassToCheckFor.IsNull() ? "" : SyncLoadedClassToCheckFor.GetAssetName();
	}
	return ClassName + FString(bTryTestAssociatedActor ? ", TriesTestingActor" : "");
}

UClass* SF::UConditional_Object_IsOfClass::ResolveClassToCheckFor() const
{
	return bPreloadClassToCheckFor ? PreLoadedClassToCheckFor.Get() : SyncLoadedClassToCheckFor.LoadSynchronous();
}

const SF::FConditionalAnswer& SF::Conditional::Answer::Error::NoClassToCheckForSpecified()
{
	static FConditionalAnswer Answer = FromErrorMsg(FString("No class to check for configured!"));
	return Answer;
}
