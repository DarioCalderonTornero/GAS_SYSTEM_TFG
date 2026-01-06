// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h" 
#include "DoorCpp.generated.h"

UCLASS()
class GAS_SYSTEM_TFG_API ADoorCpp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorCpp();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DoorMesh;
	
	bool shouldOpenOrClose;
	
	float yawIncrement;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	//FString DoorName;
	
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void OpenDoor();
	
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void CloseDoor();	
};
