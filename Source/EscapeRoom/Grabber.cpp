// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeRoom.h"
#include "Grabber.h"

//blank macro
#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	findPhysicsHandle();
	findInputComponent();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent){
		//move the object that we're holding

		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

		FVector LineTraceEnd = ReachingPosition(PlayerViewPointLocation, PlayerViewPointRotation.Vector());
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

}




void UGrabber::findPhysicsHandle(){
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle){
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle Find"));
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle Missing"));
	}
}

void UGrabber::findInputComponent(){
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent){
		UE_LOG(LogTemp, Warning, TEXT("InputComponent Find"));
		setupInput();
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("InputComponent Missing"));
	}
}

void UGrabber::setupInput(){
	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

void UGrabber::Grab(){
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));
	//try and reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	//if we hit something attach physics handle
	if (ActorHit){
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
		//Attach physics handle
	}


}

void UGrabber::Release(){
	UE_LOG(LogTemp, Warning, TEXT("Release Object"));
	
	//release object
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach(){
	//Get Player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	
	FVector LineTraceEnd = ReachingPosition(PlayerViewPointLocation, PlayerViewPointRotation.Vector());

	//UE_LOG(LogTemp, Log, TEXT("PlayerView point : Location = %s, Rotation = %s" ), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f);

	//Setup Query Parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//Ray-Cast
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

	//See what we hit 
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit){
		UE_LOG(LogTemp, Log, TEXT("Object Grabbed : %s "), *ActorHit->GetName());
	}

	return Hit;
}

const FVector UGrabber::ReachingPosition(FVector PlayerViewPointLocation, FVector PlayerViewRotation){
	return PlayerViewPointLocation + PlayerViewRotation * Reach;
}
