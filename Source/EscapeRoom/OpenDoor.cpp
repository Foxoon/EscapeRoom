// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeRoom.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Find the owning Actor
	Owner = GetOwner();

}

void UOpenDoor::OpenDoor()
{
	//Set the door rotation
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor(){
	//Set the door rotation
	Owner->SetActorRotation(FRotator(0.f, 180.f , 0.f));
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
	//Poll the Triger Volume		
	if (GetTotalMassOfActorsOnPlate() > 30.f){
		UE_LOG(LogTemp, Log, TEXT("Open Door"));
		OpenDoor();
		doorOpened = true;
		Opentime = GetWorld()->GetTimeSeconds();
	}
	
	if (doorOpened && (GetWorld()->GetTimeSeconds() - Opentime)  > DoorCloseDelay){
		UE_LOG(LogTemp, Log, TEXT("Close Door"));
		CloseDoor();
		doorOpened = false;
	}


	
	

}

float UOpenDoor::GetTotalMassOfActorsOnPlate(){
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;

	if (PressurePlate == nullptr){
		UE_LOG(LogTemp, Error, TEXT("PRESSURE PLATE NOT ASSIGNED TO THE DOOR"));
		return TotalMass;
	}

	//find all overlapping actors 
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//iterate trough all of the objects
	for (const auto* Actor : OverlappingActors){
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	UE_LOG(LogTemp, Warning, TEXT("Total Mass = %f"), TotalMass);
	return TotalMass;
}