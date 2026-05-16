// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "Conditional.h"

#include "ConditionalDebugTrace.h"
#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

void SF::UConditional::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
#if WITH_EDITOR
	UpdateTitlePropertyString();
#endif
}

#if WITH_EDITOR
EDataValidationResult SF::UConditional::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	TArray<UConditional*> ConditionalChildren = GetImmediateChildren();
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

void SF::UConditional::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UpdateTitlePropertyString();
}
#endif

SF::FConditionalAnswer SF::UConditional::EvaluateObject(UObject* TestObject)
{
	return Evaluate(FConditionalEvaluationContext{ TestObject });
}

SF::FConditionalAnswer SF::UConditional::Evaluate(const FConditionalEvaluationContext& EvaluationContext)
{
	TArray<UConditional*> ImmediateChildren = GetImmediateChildren();
	if (!GetAllowedChildrenNumRange().Contains(ImmediateChildren.Num()))
	{
		return Conditional::Answer::Error::NumChildrenUnsupported();
	}
	if (ImmediateChildren.Contains(nullptr))
	{
		return Conditional::Answer::Error::HasInvalidChild();
	}
	if (!EvaluationContext.GetTestObject())
	{
		return Conditional::Answer::Error::InvalidTestObject();
	}
	
	FConditionalDebugTrace* DebugTrace = EvaluationContext.TryGetDebugTrace();
	if (DebugTrace)
	{
		DebugTrace->PushObjectToTest(*EvaluationContext.GetTestObject());
		if (GetAllowedChildrenNumRange().GetLowerBoundValue() > 0)
		{
			DebugTrace->Indent();
		}
	}

	// the actual evaluation happens here, everything else is debug tracing & post-processing
	FConditionalAnswer Answer = EvaluateInternal(EvaluationContext);
	
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

void SF::UConditional::ForThisAndEachChildDo(const TFunction<void(UConditional*)>& Work)
{
	Work(this);
	for (UConditional* Child : GetImmediateChildren())
	{
		Child->ForThisAndEachChildDo(Work);
	}
}

TArray<SF::UConditional*> SF::UConditional::GetImmediateChildren_Implementation() const
{
	return {};
}

FInt32Range SF::UConditional::GetAllowedChildrenNumRange_Implementation() const
{
	return FInt32Range(TRangeBound<int>::Inclusive(0), TRangeBound<int>::Inclusive(0));
}

FString SF::UConditional::CreateConfigurationDebugString_Implementation() const
{
	return FString();
}

#if WITH_GAMEPLAY_DEBUGGER
void SF::UConditional::VisualizeWithGameplayDebugger(FGameplayDebuggerCategory& Debugger, FGameplayDebuggerCanvasContext& Canvas) {}
#endif WITH_GAMEPLAY_DEBUGGER

#if WITH_EDITOR
bool SF::UConditional::TryAddChild_Implementation(UConditional* Child) { return false; }
bool SF::UConditional::TryRemoveChild_Implementation(UConditional* Child) { return false; }
#endif

SF::FConditionalAnswer SF::UConditional::EvaluateInternal_Implementation(const FConditionalEvaluationContext& EvaluationContext)
{
	return Conditional::Answer::Yes();
}

#if WITH_EDITOR
FString SF::UConditional::GetPathNamePrettified() const
{
	FString DiscardedPrefix, PathToThisInAsset;
	GetPathName().Split(TEXT(":"), &DiscardedPrefix, &PathToThisInAsset);
	return PathToThisInAsset.Replace(TEXT("."), TEXT(" > "));
}
#endif

#if WITH_EDITOR
void SF::UConditional::UpdateTitlePropertyString()
{
	FString IndexString{};
	if (const auto* OuterConditional = GetTypedOuter<UConditional>())
	{
		const TArray<UConditional*> OuterConditionalChildren = OuterConditional->GetImmediateChildren();
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
