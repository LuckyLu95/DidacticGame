// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
UGrabComponent::UGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerIC = GetOwner()->FindComponentByClass<UInputComponent>();

	if (OwnerIC)
	{
		UE_LOG(LogTemp, Error, TEXT("Trovato input component"));

		OwnerIC->BindAction("Grab", IE_Pressed, this, &UGrabComponent::Grabbing);
		OwnerIC->BindAction("Grab", IE_Released, this, &UGrabComponent::Dropping);
	}
	// ...
	
}


void::UGrabComponent::Grabbing()
{
	UE_LOG(LogTemp, Error, TEXT("Afferro"));

	AActor* Possessore = GetOwner();
	FVector Start = Possessore->GetActorLocation();
	//FVector End = Start + FVector(0, 0, 300);
	FVector End = Start + Possessore->GetActorForwardVector() * 200;

	//Il draw Debug line mi permette di vedere dove sto tracciando una linea tra due punti
	DrawDebugLine(GetWorld(), Start, End, FColor::Magenta, false, -1, 0, 4.f);

	//Il line trace mi permette di verificare se tra due punti
	//e mi potra' restituire il puntatore di tale oggetto(Actor)
	FHitResult Risultato;
	FCollisionQueryParams Extra;
	Extra.AddIgnoredActor(Possessore);


	bool Tracing = GetWorld()->LineTraceSingleByObjectType(Risultato, Start, End, ECC_PhysicsBody);

	if (Tracing)
	{ 
		Grabbed = Risultato.GetActor();
	}
	
}

void::UGrabComponent::Dropping()
{
	UE_LOG(LogTemp, Error, TEXT("Rilascio"));

	Grabbed = nullptr;
}

// Called every frame
void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Possessore = GetOwner();
	FVector Start = Possessore->GetActorLocation();
	//FVector End = Start + FVector(0, 0, 300);
	FVector End = Start + Possessore->GetActorForwardVector()*200;

	//Il draw Debug line mi permette di vedere dove sto tracciando una linea tra due punti
	DrawDebugLine(GetWorld(), Start, End, FColor::Magenta,false, -1, 0, 4.f);


	if (Grabbed)
	{
		Grabbed->SetActorLocation(End);
	}

	/*if (Tracing)
	{
		UE_LOG(LogTemp,Warning,TEXT("Ho trovato %s"), *Risultato.GetActor()->GetName())
	}
	*/

	// ...
}

