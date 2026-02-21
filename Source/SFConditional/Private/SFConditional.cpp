// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "SFConditional.h"

#include "SFConditionalDebugTrace.h"
#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

void USFConditional::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
#if WITH_EDITOR
	UpdateTitlePropertyString();
#endif
}

#if WITH_EDITOR
EDataValidationResult USFConditional::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	TArray<USFConditional*> ConditionalChildren = GetImmediateChildren();
	const TRange AllowedChildrenRange = GetAllowedChildrenNumRange();
	
	if (!AllowedChildrenRange.Contains(ConditionalChildren.Num()))
	{
		Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);

		auto GetBoundBracket = [](const TRangeBound<int>& Bound, const bool bIsLower)
		{
			if (Bound.IsOpen()) return FString("inf");
			FString Str;
			if (bIsLower && Bound.IsClosed() && Bound.IsInclusive()) Str = FString("[");
			if (bIsLower && Bound.IsClosed() && Bound.IsExclusive()) Str = FString("]");
			if (!bIsLower && Bound.IsClosed() && Bound.IsInclusive()) Str = FString("]");
			if (!bIsLower && Bound.IsClosed() && Bound.IsExclusive()) Str = FString("[");
			return bIsLower ? Str + FString::FromInt(Bound.GetValue()) : FString::FromInt(Bound.GetValue()) + Str;
		};
		const FString BoundStrLower = GetBoundBracket(AllowedChildrenRange.GetLowerBound(), true);
		const FString BoundStrUpper = GetBoundBracket(AllowedChildrenRange.GetUpperBound(), false);
		
		Context.AddError(FText::FromString(FString::Printf(TEXT("Required range is '%s' children, actual num children is %d for '%s'"),
			*FString(BoundStrLower + "-" + BoundStrUpper), ConditionalChildren.Num(), *GetPathNamePrettified())));
	}

	for (int ChildIndex = 0; ChildIndex < ConditionalChildren.Num(); ++ChildIndex)
	{
		if (IsValid(ConditionalChildren[ChildIndex]))
		{
			Result = CombineDataValidationResults(Result, ConditionalChildren[ChildIndex]->IsDataValid(Context));
		}
		else
		{
			Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
			Context.AddError(FText::FromString(FString::Printf(TEXT("%s has invalid child at index %d"),
				*GetName(), ChildIndex)));
		}
	}
	
	return Result;
}

void USFConditional::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UpdateTitlePropertyString();
}
#endif

FSFConditionalAnswer USFConditional::EvaluateObject(UObject* TestObject)
{
	return Evaluate(FSFConditionalEvaluationContext{ TestObject });
}

FSFConditionalAnswer USFConditional::Evaluate(const FSFConditionalEvaluationContext& EvaluationContext)
{
	TArray<USFConditional*> ImmediateChildren = GetImmediateChildren();
	if (!GetAllowedChildrenNumRange().Contains(ImmediateChildren.Num()))
	{
		return SF::Conditional::Answer::Error::NumChildrenUnsupported();
	}
	if (ImmediateChildren.Contains(nullptr))
	{
		return SF::Conditional::Answer::Error::HasInvalidChild();
	}
	if (!EvaluationContext.GetTestObject())
	{
		return SF::Conditional::Answer::Error::InvalidTestObject();
	}
	
	FSFConditionalDebugTrace* DebugTrace = EvaluationContext.TryGetDebugTrace();
	if (DebugTrace)
	{
		DebugTrace->PushObjectToTest(*EvaluationContext.GetTestObject());
		if (GetAllowedChildrenNumRange().GetLowerBoundValue() > 0)
		{
			DebugTrace->Indent();
		}
	}

	// the actual evaluation happens here, everything else is debug tracing & post-processing
	FSFConditionalAnswer Answer = EvaluateInternal(EvaluationContext);
	
	if (DebugTrace && GetAllowedChildrenNumRange().GetLowerBoundValue() > 0)
	{
		DebugTrace->Dedent();
	}
	
	if (bIsInverted)
	{
		Answer.bBinaryAnswer = !Answer.bBinaryAnswer;
		Answer.FuzzyAnswer = FMath::Max(1.f - Answer.FuzzyAnswer, 0.f);
	}
	
	Answer.FuzzyAnswer *= Weight;
	
	if (bIsOptional)
	{
		Answer.bBinaryAnswer = true;
	}

	if (!Answer.bBinaryAnswer && !bDoesImpactScoreOnFail)
	{
		Answer.FuzzyAnswer = 0.f;
	}
	
	if (DebugTrace)
	{
		DebugTrace->PushConditionalAnswer(Answer, *this);
	}
	return Answer;
}

void USFConditional::ForThisAndEachChildDo(const TFunction<void(USFConditional*)>& Work)
{
	Work(this);
	for (USFConditional* Child : GetImmediateChildren())
	{
		Child->ForThisAndEachChildDo(Work);
	}
}

TArray<USFConditional*> USFConditional::GetImmediateChildren_Implementation() const
{
	return {};
}

FInt32Range USFConditional::GetAllowedChildrenNumRange_Implementation() const
{
	return FInt32Range(TRangeBound<int>::Inclusive(0), TRangeBound<int>::Inclusive(0));
}

FString USFConditional::CreateConfigurationDebugString_Implementation() const
{
	return FString();
}

#if WITH_GAMEPLAY_DEBUGGER
void USFConditional::VisualizeWithGameplayDebugger(FGameplayDebuggerCategory& Debugger, FGameplayDebuggerCanvasContext& Canvas) {}
#endif WITH_GAMEPLAY_DEBUGGER

#if WITH_EDITOR
bool USFConditional::TryAddChild_Implementation(USFConditional* Child) { return false; }
bool USFConditional::TryRemoveChild_Implementation(USFConditional* Child) { return false; }
#endif

FSFConditionalAnswer USFConditional::EvaluateInternal_Implementation(const FSFConditionalEvaluationContext& EvaluationContext)
{
	return SF::Conditional::Answer::Yes();
}

#if WITH_EDITOR
FString USFConditional::GetPathNamePrettified() const
{
	FString DiscardedPrefix, PathToThisInAsset;
	GetPathName().Split(TEXT(":"), &DiscardedPrefix, &PathToThisInAsset);
	return PathToThisInAsset.Replace(TEXT("."), TEXT(" > "));
}
#endif

#if WITH_EDITOR
void USFConditional::UpdateTitlePropertyString()
{
	FString IndexString{};
	if (const auto* OuterConditional = GetTypedOuter<USFConditional>())
	{
		const TArray<USFConditional*> OuterConditionalChildren = OuterConditional->GetImmediateChildren();
		IndexString = FString::Printf(TEXT("[%d] "), OuterConditionalChildren.IndexOfByKey(this));
	}
	
	const FString WeightString = FString::Printf(TEXT("[w:%s] "), *FString::Printf(TEXT("%3d%%"), FMath::RoundToInt(100.f * Weight)));
	
	const FString DisplayName = GetClass()->GetDisplayNameText().ToString();
	FString DiscardedLeftPart, CoreDisplayName;
	DisplayName.Split(" - ", &DiscardedLeftPart, &CoreDisplayName);
	
	const FString ConfigurationString = CreateConfigurationDebugString();
	const FString ConfigurationStringFull = ConfigurationString.IsEmpty() ? "" : " (" + ConfigurationString + ")";
	
	ConditionalTitlePropertyString = IndexString + WeightString + CoreDisplayName + ConfigurationStringFull;
}
#endif
