// Copyright Wloop


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}



void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetACS =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetACS == nullptr)return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetACS->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle =  TargetACS->MakeOutgoingSpec(GameplayEffectClass, 1.0f,EffectContextHandle);
	TargetACS->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	 if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	 {
		 ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	 }
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
}



