// Copyright Strayfarer & Contributors. Released under the MIT license.


#include "ConditionalDebugTrace.h"

#include "Conditional.h"

void SF::FConditionalDebugTrace::PushConditionalAnswer(const FConditionalAnswer& Answer, const UConditional& Conditional)
{
#if !UE_BUILD_SHIPPING
	Lines.Add(
		FString::ChrN(CurrentTreeDepth * 6, ' ')
		+ CreateConditionalDebugStatusString(Answer, Conditional)
	);
#endif
}

void SF::FConditionalDebugTrace::PushObjectToTest(const UObject& ObjectToTest)
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

FString SF::FConditionalDebugTrace::CreateConditionalDebugStatusString(const FConditionalAnswer& ReferenceAnswer,
	const UConditional& Conditional)
{
	FString Name = Conditional.GetName();
	Name.RemoveFromStart("Conditional_");
	int32 LastUnderscoreIdx;
	if (Name.FindLastChar('_', LastUnderscoreIdx))
	{
		Name = Name.Left(LastUnderscoreIdx);
	}
	
	if (ReferenceAnswer.IsError())
	{
		static FText FormatTextError = FText::FromString("{Red}{error}, {name}{inverted}{reasoning}");
		
		return FText::FormatNamed(FormatTextError,
			TEXT("error"),     FText::FromString(ReferenceAnswer.GetErrorMessage().ToString()),
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

FString SF::FConditionalDebugTrace::ToString() const
{
	FString Result;
	for (const auto& Line : Lines)
	{
		Result = Line + TEXT("\n") + Result;
	}
	return Result;
}
