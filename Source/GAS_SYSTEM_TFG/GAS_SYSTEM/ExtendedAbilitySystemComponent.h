// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ExtendedAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAS_SYSTEM_TFG_API UExtendedAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
protected: 
	TArray<FGameplayAbilitySpec> LastActivableAbilities;

public:
	// Sets default values for this component's properties
	UExtendedAbilitySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void OnRep_ActivateAbilities() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
