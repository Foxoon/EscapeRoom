// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private :
	UPROPERTY(EditAnywhere)		
		float Reach = 100.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	void findPhysicsHandle();
	void findInputComponent();
	void setupInput();

	//return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	//ray-cast and grab
	void Grab(); 

	void Release();

	const FVector ReachingPosition(FVector PlayerViewPointLocation, FVector PlayerViewRotation);


};
