// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFirstScriptTest.generated.h"

UCLASS()
class GAS_SYSTEM_TFG_API AMyFirstScriptTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFirstScriptTest();

protected:
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My First Script Test")
	FString Name;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My First Script Test")
	FString Name3;
};
