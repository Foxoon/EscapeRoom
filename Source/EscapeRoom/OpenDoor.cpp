// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeRoom.h"
#include "OpenDoor.h"


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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

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
	// If the actor that should open is in the volume
	
	//UE_LOG(LogTemp, Log, TEXT("ActorThatOpens  =  %s" ), *ActorThatOpens->GetActorLabel());
	
	
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)){
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

