// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtendedAbilitySystemComponent.h"

#include "Character/GameCharacterBase.h"


// Sets default values for this component's properties
UExtendedAbilitySystemComponent::UExtendedAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UExtendedAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UExtendedAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	
	AGameCharacterBase * Character = Cast<AGameCharacterBase>(GetOwner());
	if (!Character)
		return;
	
	bool bAbilitiesChanged = false;
	if (LastActivableAbilities.Num() != ActivatableAbilities.Items.Num())
	{
		bAbilitiesChanged = true;
	}
	else
	{
		for (int32 i = 0; i < LastActivableAbilities.Num(); ++i)
		{ 
			if (LastActivableAbilities[i].Ability != ActivatableAbilities.Items[i].Ability) 
			{
				bAbilitiesChanged = true;
				break;
			}
		}
	}
	if (bAbilitiesChanged)
	{
		Character->SendAbilitiesChangedEvent();
		LastActivableAbilities = ActivatableAbilities.Items;
	}
}


// Called every frame
void UExtendedAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

