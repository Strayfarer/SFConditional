// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "ConditionalTypes/Logic/SFConditional_Logic_Or.h"
#include "ConditionalTypes/Utility/SFConditional_Utility_AlwaysFalse.h"
#include "ConditionalTypes/Utility/SFConditional_Utility_AlwaysTrue.h"
#include "Misc/AutomationTest.h"
#include "Mocks/MockObject.h"

using namespace SF::Conditional;

BEGIN_DEFINE_SPEC(FConditionalTypeLogicOrSpec, "SF.Conditional.Types.Logic.Or", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TObjectPtr<USFConditional_Logic_Or> Sut = nullptr;
	TObjectPtr<UObject> Object;
END_DEFINE_SPEC(FConditionalTypeLogicOrSpec)

void FConditionalTypeLogicOrSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<USFConditional_Logic_Or>();
		Object = NewObject<UMockObject>();
	});
	Describe("with two true children", [this]
	{
		It("should yield a yes answer", [this]
		{
			Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
			Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Yes());
		});
	});
	Describe("with one true, one false child", [this]
	{
		It("should yield a yes answer", [this]
		{
			Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
			Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Yes());
		});
	});
	Describe("with two false children", [this]
	{
		It("should yield a no answer", [this]
		{
			Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
			Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysFalse>());
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::No());
		});
	});
	Describe("with one child", [this]
	{
		It("should yield NumChildrenUnsupported error state", [this]
		{
			Sut->TryAddChild(NewObject<USFConditional_Utility_AlwaysTrue>());
			TestEqual("Conditional Answer", Sut->EvaluateObject(Object), Answer::Error::NumChildrenUnsupported());
		});
	});
}

#endif WITH_AUTOMATION_WORKER