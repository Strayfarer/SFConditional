// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "Misc/AutomationTest.h"
#include "ConditionalTypes/Logic/SFConditional_Logic_Not.h"
#include "ConditionalTypes/Utility/SFConditional_Utility_AlwaysFalse.h"
#include "ConditionalTypes/Utility/SFConditional_Utility_AlwaysTrue.h"
#include "Mocks/MockObject.h"

BEGIN_DEFINE_SPEC(FConditionalTypeLogicNotSpec, "SF.Conditional.Types.Logic.Not", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TObjectPtr<USFConditional_Logic_Not> Sut = nullptr;
	TObjectPtr<UObject> Object;
END_DEFINE_SPEC(FConditionalTypeLogicNotSpec)

void FConditionalTypeLogicNotSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<USFConditional_Logic_Not>();
		Object = NewObject<UMockObject>();
	});
	Describe("with a true child", [this]
	{
		It("should yield a no answer", [this]
		{
			Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), SF::Conditional::Answer::No());
		});
	});
	Describe("with a false child", [this]
	{
		It("should yield a yes answer", [this]
		{
			Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), SF::Conditional::Answer::Yes());
		});
	});
	Describe("adding two children", [this]
	{
		It("should reject adding any children after the first", [this]
		{
			Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
			const bool bCouldAddSecondChild = Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
			TestFalse("Could Add Second Child", bCouldAddSecondChild);
		});
	});
}

#endif WITH_AUTOMATION_WORKER