// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "Misc/AutomationTest.h"
#include "Mocks/Conditional_MockConditional.h"

using namespace SF::Conditional;

BEGIN_DEFINE_SPEC(FConditionalAnswerSpec, "SF.Conditional.Answer", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	SF::FConditionalAnswer Sut{};
END_DEFINE_SPEC(FConditionalAnswerSpec)

void FConditionalAnswerSpec::Define()
{
	Describe("ErrorState", [this]
	{
		Describe("a YES answer", [this]
		{
			It("should NOT be regarded as an error", [this]
			{
				TestFalse("Is Error", Answer::Yes().IsError());
			});
		});
		Describe("a NO answer", [this]
		{
			It("should NOT be regarded as an error", [this]
			{
				TestFalse("Is Error", Answer::No().IsError());
			});
		});
		Describe("an ERROR answer", [this]
		{
			It("should be regarded as an error", [this]
			{
				TestTrue("Is Error", Answer::Error::MockA().IsError());
			});
		});
	});
	Describe("Comparisons", [this]
	{
		Describe("two YES answers", [this]
		{
			It("should be equal", [this]
			{
				TestEqual("Conditional Answer", Answer::Yes(), Answer::Yes());
			});
		});
		Describe("a YES and a NO answer", [this]
		{
			It("should be NOT equal", [this]
			{
				TestNotEqual("Conditional Answer", Answer::Yes(), Answer::No());
			});
		});
		Describe("two NO answers", [this]
		{
			It("should be equal", [this]
			{
				TestEqual("Conditional Answer", Answer::No(), Answer::No());
			});
		});
		Describe("a [yes, 0,5] and a [yes, 0,7] answer", [this]
		{
			It("should NOT be equal", [this]
			{
				TestNotEqual("Conditional Answer", Answer::Create(true, 0.5f), Answer::Create(true, 0.7f));
			});
		});
		Describe("a [no, 0,5] and a [no, 0,7] answer", [this]
		{
			It("should NOT be equal", [this]
			{
				TestNotEqual("Conditional Answer", Answer::Create(false, 0.5f), Answer::Create(false, 0.7f));
			});
		});
		Describe("a [yes, 0,7] and a [no, 0,7] answer", [this]
		{
			It("should NOT be equal", [this]
			{
				TestNotEqual("Conditional Answer", Answer::Create(true, 0.7f), Answer::Create(false, 0.7f));
			});
		});
		Describe("two ERROR answers of same kind", [this]
		{
			It("should be equal", [this]
			{
				TestEqual("Conditional Answer", Answer::Error::MockA(), Answer::Error::MockA());
			});
		});
		Describe("two ERROR answers of different kind", [this]
		{
			It("should be NOT equal", [this]
			{
				TestNotEqual("Conditional Answer", Answer::Error::MockA(), Answer::Error::MockB());
			});
		});
		Describe("a YES answer and an ERROR answer", [this]
		{
			It("should be NOT equal", [this]
			{
				TestNotEqual("Conditional Answer", Answer::Yes(), Answer::Error::MockA());
			});
		});
		Describe("a NO answer and an ERROR answer", [this]
		{
			It("should be NOT equal", [this]
			{
				TestNotEqual("Conditional Answer", Answer::No(), Answer::Error::MockA());
			});
		});
	});
}

#endif WITH_AUTOMATION_WORKER