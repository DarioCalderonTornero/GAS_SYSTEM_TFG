// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MyPlayerGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_SYSTEM_TFG_API UMyPlayerGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool bShouldShowAbilityBar = false;
		
	
};
