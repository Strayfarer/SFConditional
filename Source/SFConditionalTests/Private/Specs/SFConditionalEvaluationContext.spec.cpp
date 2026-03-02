// Copyright Strayfarer & Contributors. Released under the MIT license.

#if WITH_AUTOMATION_WORKER

#include "SFConditionalEvaluationContext.h"
#include "Misc/AutomationTest.h"
#include "Mocks/SFConditional_MockActorComponent.h"
#include "Mocks/SFConditional_MockObject.h"
#include "TestWorld/AutomationTestWorld.h"

BEGIN_DEFINE_SPEC(FConditionalEvaluationContextSpec, "SF.Conditional.EvaluationContext", EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	TSharedPtr<WeekendUtils::FScopedAutomationTestWorld> TestWorld;
	TObjectPtr<UObject> Object;
	TObjectPtr<AActor> Actor;
	TObjectPtr<UActorComponent> ActorComponent;
	TObjectPtr<USceneComponent> SceneComponent;
	FSFConditionalEvaluationContext EvaluationContext;
END_DEFINE_SPEC(FConditionalEvaluationContextSpec)

void FConditionalEvaluationContextSpec::Define()
{
	BeforeEach([this]
	{
		TestWorld = MakeShared<WeekendUtils::FScopedAutomationTestWorld>("TestWorld");
		TestWorld->InitializeGame();
	});
	AfterEach([this]
	{
		TestWorld.Reset();
	});
	
	Describe("with UObject as object to test", [this]
	{
		BeforeEach([this]
		{
			Object = NewObject<USFConditional_MockObject>();
			EvaluationContext = FSFConditionalEvaluationContext(Object, nullptr);
		});
		It("should yield that context world is equal to object to test world", [this]
		{
			TestEqual("Context World", EvaluationContext.GetWorld(), Object->GetWorld());
		});
		It("should yield valid TestObject object", [this]
		{
			TestTrue("TestObject Object", IsValid(EvaluationContext.GetTestObject()));
		});
		It("should yield invalid TestObject actor", [this]
		{
			TestFalse("TestObject Actor", IsValid(EvaluationContext.TryGetTestObjectActor()));
		});
		It("should yield invalid TestObject actor component", [this]
		{
			TestFalse("TestObject ActorComponent", IsValid(EvaluationContext.TryGetTestObjectActorComponent<UActorComponent>()));
		});
		It("should yield invalid TestObject transform", [this]
		{
			TestFalse("TestObject Transform", EvaluationContext.TryGetTestObjectTransform().IsSet());
		});
	});
	
	
	Describe("with AActor as object to test", [this]
	{
		BeforeEach([this]
		{
			Actor = TestWorld->AsRef().SpawnActor<AActor>();
			EvaluationContext = FSFConditionalEvaluationContext(Actor, nullptr);
		});
		It("should yield valid TestObject object", [this]
		{
			TestTrue("TestObject Object", IsValid(EvaluationContext.GetTestObject()));
		});
		It("should yield valid TestObject actor", [this]
		{
			TestTrue("TestObject Actor", IsValid(EvaluationContext.TryGetTestObjectActor()));
		});
		It("should yield invalid TestObject actor component", [this]
		{
			TestFalse("TestObject ActorComponent", IsValid(EvaluationContext.TryGetTestObjectActorComponent<UActorComponent>()));
		});
		It("should yield valid TestObject transform", [this]
		{
			TestTrue("TestObject Transform", EvaluationContext.TryGetTestObjectTransform()->IsValid());
		});
	});
	
	
	Describe("with AActor with UMockActorComponent as object to test", [this]
	{
		BeforeEach([this]
		{
			Actor = TestWorld->AsRef().SpawnActor<AActor>();
			ActorComponent = Actor->AddComponentByClass(USFConditional_MockActorComponent::StaticClass(), false, {}, false);
			EvaluationContext = FSFConditionalEvaluationContext(Actor, nullptr);
		});
		It("should yield valid TestObject object", [this]
		{
			TestTrue("TestObject Object", IsValid(EvaluationContext.GetTestObject()));
		});
		It("should yield valid TestObject actor", [this]
		{
			TestTrue("TestObject Actor", IsValid(EvaluationContext.TryGetTestObjectActor()));
		});
		It("should yield valid TestObject actor component", [this]
		{
			TestTrue("TestObject ActorComponent", IsValid(EvaluationContext.TryGetTestObjectActorComponent<UActorComponent>()));
		});
		It("should yield valid TestObject mock actor component", [this]
		{
			TestTrue("TestObject ActorComponent", IsValid(EvaluationContext.TryGetTestObjectActorComponent<USFConditional_MockActorComponent>()));
		});
		It("should yield valid TestObject transform", [this]
		{
			TestTrue("TestObject Transform", EvaluationContext.TryGetTestObjectTransform()->IsValid());
		});
	});
	
	
	Describe("with UMockActorComponent as object to test", [this]
	{
		BeforeEach([this]
		{
			Actor = TestWorld->AsRef().SpawnActor<AActor>();
			ActorComponent = Actor->AddComponentByClass(USFConditional_MockActorComponent::StaticClass(), false, {}, false);
			EvaluationContext = FSFConditionalEvaluationContext(ActorComponent, nullptr);
		});
		It("should yield valid TestObject object", [this]
		{
			TestTrue("TestObject Object", IsValid(EvaluationContext.GetTestObject()));
		});
		It("should yield valid TestObject actor", [this]
		{
			TestTrue("TestObject Actor", IsValid(EvaluationContext.TryGetTestObjectActor()));
		});
		It("should yield valid TestObject actor component", [this]
		{
			TestTrue("TestObject ActorComponent", IsValid(EvaluationContext.TryGetTestObjectActorComponent<UActorComponent>()));
		});
		It("should yield valid TestObject mock actor component", [this]
		{
			TestTrue("TestObject ActorComponent", IsValid(EvaluationContext.TryGetTestObjectActorComponent<USFConditional_MockActorComponent>()));
		});
		It("should yield valid TestObject transform", [this]
		{
			TestTrue("TestObject Transform", EvaluationContext.TryGetTestObjectTransform()->IsValid());
		});
	});
	
	
	Describe("with USceneComponent as object to test", [this]
	{
		BeforeEach([this]
		{
			Actor = TestWorld->AsRef().SpawnActor<AActor>();
			ActorComponent = Actor->AddComponentByClass(USceneComponent::StaticClass(), false, {}, false);
			SceneComponent = Cast<USceneComponent>(ActorComponent);
			SceneComponent->SetWorldLocation(FVector(100.0f, 0.0f, 0.0f));
			EvaluationContext = FSFConditionalEvaluationContext(SceneComponent, nullptr);
		});
		It("should yield valid TestObject object", [this]
		{
			TestTrue("TestObject Object", IsValid(EvaluationContext.GetTestObject()));
		});
		It("should yield valid TestObject actor", [this]
		{
			TestTrue("TestObject Actor", IsValid(EvaluationContext.TryGetTestObjectActor()));
		});
		It("should yield valid TestObject actor component", [this]
		{
			TestTrue("TestObject ActorComponent", IsValid(EvaluationContext.TryGetTestObjectActorComponent<UActorComponent>()));
		});
		It("should yield valid TestObject transform", [this]
		{
			TestTrue("TestObject Transform", EvaluationContext.TryGetTestObjectTransform()->IsValid());
		});
		It("should yield TestObject transform equal to the USceneComponent transform", [this]
		{
			TestEqual("TestObject Transform", 
				EvaluationContext.TryGetTestObjectTransform().Get(FTransform::Identity),
				SceneComponent->GetComponentTransform());
		});
	});
}

#endif WITH_AUTOMATION_WORKER