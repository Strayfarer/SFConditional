// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "SFConditionalDebugTrace.h"

#include "SFConditional.h"

void FSFConditionalDebugTrace::PushConditionalAnswer(const FSFConditionalAnswer& Answer, const USFConditional& Conditional)
{
#if !UE_BUILD_SHIPPING
	Lines.Add(
		FString::ChrN(IndentLevel * 6, ' ')
		+ CreateConditionalDebugStatusString(Answer, Conditional)
	);
#endif
}

void FSFConditionalDebugTrace::PushObjectToTest(const UObject& ObjectToTest)
{
#if !UE_BUILD_SHIPPING
	if (bHasObjectToTestBeenPushed) return;
	bHasObjectToTestBeenPushed = true;
	
	if (const AActor* TargetOwnerActor = Cast<AActor>(ObjectToTest.GetOuter()))
	{
		Lines.Add("{white}" + TargetOwnerActor->GetName() + " > " + ObjectToTest.GetName());
	}
	else
	{
		Lines.Add("{white}" + ObjectToTest.GetName());
	}
#endif
}

FString FSFConditionalDebugTrace::CreateConditionalDebugStatusString(const FSFConditionalAnswer& ReferenceAnswer,
	const USFConditional& Conditional)
{
	FString Name = Conditional.GetName();
	Name.RemoveFromStart("Conditional_");
	int32 LastUnderscoreIdx;
	Name.FindLastChar('_', LastUnderscoreIdx);
	Name = Name.Left(LastUnderscoreIdx);
	
	if (ReferenceAnswer.IsError())
	{
		static FText FormatTextError = FText::FromString("{Red}{error}, {name}{inverted}{reasoning}");
		
		return FText::FormatNamed(FormatTextError,
			TEXT("name"),      FText::FromString(Name),
			TEXT("inverted"),  FText::FromString(Conditional.IsInverted() ? " (inverted)" : ""),
			TEXT("reasoning"), FText::FromString(" " + Conditional.CreateConfigurationDebugString())
		).ToString();
	}
	else
	{
		static FText FormatTextNoError = FText::FromString("{color}Score: {score}, Weight: {weight}, {name}{inverted}{reasoning}");
	
		FString Color = "";
		if (ReferenceAnswer.GetBinaryAnswer())			 Color = "{Green}";
		else if (ReferenceAnswer.GetFuzzyAnswer() > 0.f) Color = "{Yellow}";
		else											 Color = "{Grey}";
	
		return FText::FormatNamed(FormatTextNoError,
			TEXT("color"),     FText::FromString(Color),
			TEXT("score"),     FText::FromString(FString::SanitizeFloat(ReferenceAnswer.GetFuzzyAnswer(), 2)),
			TEXT("weight"),    FText::FromString(FString::SanitizeFloat(Conditional.GetWeight(), 2)),
			TEXT("name"),      FText::FromString(Name),
			TEXT("inverted"),  FText::FromString(Conditional.IsInverted() ? " (inverted)" : ""),
			TEXT("reasoning"), FText::FromString(" " + Conditional.CreateConfigurationDebugString())
		).ToString();
	}
}

FString FSFConditionalDebugTrace::ToString() const
{
	FString Result;
	for (const auto& Line : Lines)
	{
		Result = Line + TEXT("\n") + Result;
	}
	return Result;
}
