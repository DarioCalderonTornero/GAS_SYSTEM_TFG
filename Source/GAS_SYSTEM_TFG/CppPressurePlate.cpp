// Fill out your copyright notice in the Description page of Project Settings.

#include "CppPressurePlate.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"

// Sets default values
ACppPressurePlate::ACppPressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Root componenet Set Up + Mesh Set Up
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	pressurePlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PressurePlateMesh"));
    pressurePlateMesh->SetupAttachment(RootComponent);
	//Sphere Collision Set Up
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(pressurePlateMesh);
	SphereCollision->SetSphereRadius(100);
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ACppPressurePlate::OnPressurePlatePressed);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ACppPressurePlate::OnPressurePlateReleased);
}

// Called when the game starts or when spawned
void ACppPressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACppPressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACppPressurePlate::OnPressurePlatePressed_Implementation(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	//Si el actor que ha entrado en la colision es un personaje (nuestro personaje)
	// y tenemos referencia a la puerta válida (al poner un && lo siguiente es un bool).
	if (OtherActor->IsA(ACharacter::StaticClass()) && doorRef)
	{
		doorRef->OpenDoor();
		pressurePlateMesh->SetMaterial(0, pressedPlateMeshMaterial);
		
	}
}

void ACppPressurePlate::OnPressurePlateReleased_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ACharacter::StaticClass()) && doorRef)
	{
		doorRef->CloseDoor();
		pressurePlateMesh->SetMaterial(0, defaultPlateMeshMaterial);
	}
	
}

