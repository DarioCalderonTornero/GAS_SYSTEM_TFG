// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorCpp.h"

// Sets default values
ADoorCpp::ADoorCpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoorCpp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (shouldOpenOrClose)
	{
		FRotator currentRotation = GetActorRotation();
		FRotator newRotation;
		newRotation.Pitch = currentRotation.Pitch;
		newRotation.Roll = currentRotation.Roll;
		newRotation.Yaw = currentRotation.Yaw + yawIncrement;
		SetActorRotation(newRotation);
		
		if ((yawIncrement > 0 && newRotation.Yaw >= 90.0f) || (yawIncrement < 0 && newRotation.Yaw <= 0.0f))
		{
			shouldOpenOrClose = false;
		}
	}
}


void ADoorCpp::OpenDoor()
{
	if (GetActorRotation().Yaw < 90.0f)
	{
		yawIncrement = 2;
		shouldOpenOrClose = true;
	}
}

void ADoorCpp::CloseDoor()
{
	if (GetActorRotation().Yaw >= 90)
	{
		yawIncrement = -2;
		shouldOpenOrClose = true;
	}
}

