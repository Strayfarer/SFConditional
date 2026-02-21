// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "SFConditionalAnswer.h"
#include "SFConditionalDebugTrace.generated.h"

class USFConditional;

/**
 * Helper struct to construct a multiline string representing the state of a
 * conditional tree.
 *
 * Note that the debug trace won't do anything in shipping builds!
 */
USTRUCT(BlueprintType)
struct SFCONDITIONAL_API FSFConditionalDebugTrace
{
	GENERATED_BODY()
	
	friend USFConditional;
	
	FSFConditionalDebugTrace() = default;
	
	/** Build and return the string of the current trace state. */
	FString ToString() const;
	
private:
	void PushConditionalAnswer(const FSFConditionalAnswer& Answer, const USFConditional& Conditional);
	void PushObjectToTest(const UObject& ObjectToTest);

	static FString CreateConditionalDebugStatusString(const FSFConditionalAnswer& ReferenceAnswer, const USFConditional& Conditional);
	
	FORCEINLINE void Indent() { IndentLevel++; }
	FORCEINLINE void Dedent() { IndentLevel = FMath::Max(0, IndentLevel - 1); }
	
	TArray<FString> Lines;
	int32 IndentLevel = 0;
	bool bHasObjectToTestBeenPushed = false;
};
