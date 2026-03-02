// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "ConditionalTypes/Area/SFConditional_Area_WorldDistanceRadius.h"
#include "Misc/AutomationTest.h"
#include "Mocks/SFConditional_MockActor.h"
#include "Mocks/SFConditional_MockObject.h"
#include "TestWorld/AutomationTestWorld.h"

using namespace SF::Conditional;

BEGIN_DEFINE_SPEC(FConditionalTypeAreaWorldDistanceRadiusSpec, "SF.Conditional.Types.Area.WorldDistanceRadius", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TSharedPtr<WeekendUtils::FScopedAutomationTestWorld> TestWorld;
	TObjectPtr<USFConditional_Area_WorldDistanceRadius> Sut = nullptr;
	TObjectPtr<UObject> TestObjectObject;
	TObjectPtr<AActor> TestObjectActor;
	TObjectPtr<UObject> InstigatorObject;
	TObjectPtr<AActor> InstigatorActor;
END_DEFINE_SPEC(FConditionalTypeAreaWorldDistanceRadiusSpec)

void FConditionalTypeAreaWorldDistanceRadiusSpec::Define()
{
	BeforeEach([this]
	{
		Sut = NewObject<USFConditional_Area_WorldDistanceRadius>();
		
		TestWorld = MakeShared<WeekendUtils::FScopedAutomationTestWorld>("TestWorld");
		TestWorld->InitializeGame();
		
		TestObjectObject = InstigatorObject = NewObject<USFConditional_MockObject>();
		
		TestObjectActor = TestWorld->AsRef().SpawnActor<ASFConditional_MockActor>();
		InstigatorActor = TestWorld->AsRef().SpawnActor<ASFConditional_MockActor>();
	});
	AfterEach([this]
	{
		TestWorld.Reset();
	});
	
	Describe("with UObject test object", [this]
	{
		It("should yield TestObject::NoTransformProvider error state", [this]
		{
			TestEqual("Conditional Answer", 
				Sut->EvaluateObject(TestObjectObject), 
				Answer::Error::TestObject::NoTransformProvider(TestObjectObject));
		});
	});
	Describe("with no instigator", [this]
	{
		It("should yield Instigator::NoTransformProvider error state", [this]
		{
			TestEqual("Conditional Answer", 
				Sut->Evaluate({ TestObjectActor, nullptr }), 
				Answer::Error::Instigator::NoTransformProvider(nullptr));
		});
	});
	Describe("with UObject instigator", [this]
	{
		It("should yield Instigator::NoTransformProvider error state", [this]
		{
			TestEqual("Conditional Answer", 
				Sut->Evaluate({ TestObjectActor, InstigatorObject }), 
				Answer::Error::Instigator::NoTransformProvider(InstigatorObject));
		});
	});
	
	Describe("with radius 0,0", [this]
	{
		BeforeEach([this]
		{
			Sut->SetRadius(0.f);
		});
		Describe("with test object and instigator at origin", [this]
		{
			It("should yield answer Yes", [this]
			{
				TestEqual("Conditional Answer", 
					Sut->Evaluate({ TestObjectActor, InstigatorActor }), Answer::Yes());
			});
		});
		Describe("with test object and instigator at same location (not origin)", [this]
		{
			It("should yield answer Yes", [this]
			{
				TestObjectActor->SetActorLocation(FVector{ 10.f, 0.f, 0.f });
				InstigatorActor->SetActorLocation(FVector{ 10.f, 0.f, 0.f });
				TestEqual("Conditional Answer", 
					Sut->Evaluate({ TestObjectActor, InstigatorActor }), Answer::Yes());
			});
		});
		Describe("with test object and instigator at different location", [this]
		{
			It("should yield answer No", [this]
			{
				TestObjectActor->SetActorLocation(FVector{ 0.f, 0.f, 0.f });
				InstigatorActor->SetActorLocation(FVector{ 10.f, 0.f, 0.f });
				TestEqual("Conditional Answer", 
					Sut->Evaluate({ TestObjectActor, InstigatorActor }), Answer::No());
			});
		});
	});
	
	Describe("with radius 100,0", [this]
	{
		BeforeEach([this]
		{
			Sut->SetRadius(100.f);
		});
		Describe("with test object and instigator at origin", [this]
		{
			It("should yield answer Yes", [this]
			{
				TestEqual("Conditional Answer", 
					Sut->Evaluate({ TestObjectActor, InstigatorActor }), Answer::Yes());
			});
		});
		Describe("with test object and instigator at same location (not origin)", [this]
		{
			It("should yield answer Yes", [this]
			{
				TestObjectActor->SetActorLocation(FVector{ 10.f, 0.f, 0.f });
				InstigatorActor->SetActorLocation(FVector{ 10.f, 0.f, 0.f });
				TestEqual("Conditional Answer", 
					Sut->Evaluate({ TestObjectActor, InstigatorActor }), Answer::Yes());
			});
		});
		Describe("with test object at origin and instigator at 10,0,0", [this]
		{
			It("should yield answer [ true | 0,9 ]", [this]
			{
				TestObjectActor->SetActorLocation(FVector{ 0.f, 0.f, 0.f });
				InstigatorActor->SetActorLocation(FVector{ 10.f, 0.f, 0.f });
				TestEqual("Conditional Answer", 
					Sut->Evaluate({ TestObjectActor, InstigatorActor }), 
					Answer::Create(true, 0.9f));
			});
		});
		Describe("with test object at origin and instigator at 100,0,0", [this]
		{
			It("should yield answer [ true | 0,0 ]", [this]
			{
				TestObjectActor->SetActorLocation(FVector{ 0.f, 0.f, 0.f });
				InstigatorActor->SetActorLocation(FVector{ 100.f, 0.f, 0.f });
				TestEqual("Conditional Answer", 
					Sut->Evaluate({ TestObjectActor, InstigatorActor }), 
					Answer::Create(true, 0.0f));
			});
		});
		Describe("with test object at origin and instigator at 120,0,0", [this]
		{
			It("should yield answer No", [this]
			{
				TestObjectActor->SetActorLocation(FVector{ 0.f, 0.f, 0.f });
				InstigatorActor->SetActorLocation(FVector{ 120.f, 0.f, 0.f });
				TestEqual("Conditional Answer", 
					Sut->Evaluate({ TestObjectActor, InstigatorActor }), Answer::No());
			});
		});
	});
}

#endif WITH_AUTOMATION_WORKER