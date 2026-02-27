// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerGameplayAbility.h"

UMyPlayerGameplayAbility::UMyPlayerGameplayAbility()
{
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Active")));
}
