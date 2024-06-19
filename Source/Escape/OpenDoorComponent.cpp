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

	if (!AntaDaAprire) { UE_LOG(LogTemp, Error, TEXT("Manca AntaDaAprire")); return; }

	

	Trigger = GetWorld()->GetFirstPlayerController()->GetPawn();

	StartAngle = AntaDaAprire->GetComponentRotation();

	if (!Trigger) { UE_LOG(LogTemp, Error, TEXT("Manca Trigger")); return; }
	// ...
	

}

void UOpenDoorComponent::OpenDoor(float DeltaTime)
{
	FRotator StartRot = AntaDaAprire->GetComponentRotation();

	/*if (abs(StartRot.Yaw)<OpenAngle)
	{ 
		StartRot.Yaw -= (OpenAngle / OpeningTime * DeltaTime);

		AntaDaAprire->SetWorldRotation(StartRot);
	}
	else bClose = false;*/

	if (OffSetDeg < OpenAngle)
	{
		StartRot.Yaw -= (OpenAngle / OpeningTime * DeltaTime);

		OffSetDeg += (OpenAngle / OpeningTime * DeltaTime);

		AntaDaAprire->SetWorldRotation(StartRot);
	}
	//else bClosed = false;


}

void UOpenDoorComponent::CloseDoor(float DeltaTime)
{
	FRotator StartRot = AntaDaAprire->GetComponentRotation();

	/*if (StartRot.Yaw < StartAngle.Yaw)
	{
		StartRot.Yaw += (OpenAngle / OpeningTime * DeltaTime);

		AntaDaAprire->SetWorldRotation(StartRot);
	}
	else bClose = true;*/
	//UE_LOG(LogTemp, Error, TEXT("Inizio Timer chiusura.."));
	

	if (OffSetDeg > 0)
	{
		//UE_LOG(LogTemp, Error, TEXT("Chiudendo"));
		StartRot.Yaw += (OpenAngle / OpeningTime * DeltaTime);

		OffSetDeg -= (OpenAngle / OpeningTime * DeltaTime);

		AntaDaAprire->SetWorldRotation(StartRot);
	}
	//else bClosed = true; 
	
}

void UOpenDoorComponent::DelayCloseDoor()
{
	bClosed = true;
}


// Called every frame
void UOpenDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Trigger || !TriggerBox) return;

	if(TriggerBox->IsOverlappingActor(Trigger) && bClosed)
	{
		bClosed = false;
		
	}
	else
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(TimerCloseDoor))
		{
			GetWorld()->GetTimerManager().SetTimer(TimerCloseDoor, this, &UOpenDoorComponent::DelayCloseDoor, DelayClose, false);
		}

		
	}

	if(!bClosed) OpenDoor(DeltaTime);
	else CloseDoor(DeltaTime);

	// ...
}

