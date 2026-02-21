// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalTypes/Object/SFConditional_Object_IsOfClass.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#if WITH_EDITOR
EDataValidationResult USFConditional_Object_IsOfClass::IsDataValid(class FDataValidationContext& Context) const
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

void USFConditional_Object_IsOfClass::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
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

FSFConditionalAnswer USFConditional_Object_IsOfClass::EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext)
{
	using namespace SF::Conditional;
	if (bTryTestAssociatedActor)
	{
		if (const AActor* Actor = EvaluationContext.TryGetTestObjectActor())
		{
			return Answer::FromBool(Actor->IsA(ResolveClassToCheckFor()));
		}
	}
	return Answer::FromBool(EvaluationContext.GetTestObject()->IsA(ResolveClassToCheckFor()));
}

FString USFConditional_Object_IsOfClass::CreateConfigurationDebugString_Implementation() const
{
	const UClass* ClassToCheckFor = ResolveClassToCheckFor();
	return FString(ClassToCheckFor ? ClassToCheckFor->GetName() : "")
		+ FString(bTryTestAssociatedActor ? ", TriesTestingActor" : "");
}

UClass* USFConditional_Object_IsOfClass::ResolveClassToCheckFor() const
{
	return bPreloadClassToCheckFor ? PreLoadedClassToCheckFor.Get() : SyncLoadedClassToCheckFor.LoadSynchronous();
}
