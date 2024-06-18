// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoorComponent.h"

// Sets default values for this component's properties
UOpenDoorComponent::UOpenDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorComponent::BeginPlay()
{
	Super::BeginPlay();

	Trigger = GetWorld()->GetFirstPlayerController()->GetPawn();

	StartAngle = AntaDaAprire->GetComponentRotation();

	// ...
	

}

void UOpenDoorComponent::OpenDoor(float DeltaTime)
{
	FRotator StartRot = AntaDaAprire->GetComponentRotation();

	if(abs(StartRot.Yaw)<OpenAngle)
	{ 
		StartRot.Yaw -= (OpenAngle / OpeningTime * DeltaTime);

		AntaDaAprire->SetWorldRotation(StartRot);
	}
	else bClose = false;

	
}

void UOpenDoorComponent::CloseDoor(float DeltaTime)
{
	FRotator StartRot = AntaDaAprire->GetComponentRotation();

	if (StartRot.Yaw < StartAngle.Yaw)
	{
		StartRot.Yaw += (OpenAngle / OpeningTime * DeltaTime);

		AntaDaAprire->SetWorldRotation(StartRot);
	}
	else bClose = true;
}


// Called every frame
void UOpenDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Trigger || !TriggerBox) return;

	if(TriggerBox->IsOverlappingActor(Trigger) && bClose)
	{
		OpenDoor(DeltaTime);
		
	}
	else if(!TriggerBox->IsOverlappingActor(Trigger) && !bClose)
	{
		CloseDoor(DeltaTime);
	}

	// ...
}

