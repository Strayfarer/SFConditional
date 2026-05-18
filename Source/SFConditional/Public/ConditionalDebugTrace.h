// Copyright Strayfarer & Contributors. Released under the MIT license.

#pragma once

#include "CoreMinimal.h"
#include "ConditionalAnswer.h"
#include "ConditionalDebugTrace.generated.h"

namespace SF
{
	class UConditional;

	/**
	 * Helper struct to construct a multiline string representing the state of a
	 * conditional tree.
	 *
	 * Note that the debug trace won't do anything in shipping builds!
	 */
	USTRUCT(BlueprintType)
	struct SFCONDITIONAL_API FConditionalDebugTrace
	{
		GENERATED_BODY()

		friend UConditional;

		FConditionalDebugTrace() = default;

		/** Build and return the string of the current trace state. */
		FString ToString() const;

	private:
		void PushConditionalAnswer(const FConditionalAnswer& Answer, const UConditional& Conditional);
		void PushObjectToTest(const UObject& ObjectToTest);

		static FString CreateConditionalDebugStatusString(const FConditionalAnswer& ReferenceAnswer,
		                                                  const UConditional& Conditional);

		FORCEINLINE void BeginChildSection() { CurrentTreeDepth++; }
		FORCEINLINE void EndChildSection() { CurrentTreeDepth = FMath::Max(0, CurrentTreeDepth - 1); }

		TArray<FString> Lines;
		int32 CurrentTreeDepth = 0;
		bool bHasObjectToTestBeenPushed = false;
	};
}
