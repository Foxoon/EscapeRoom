// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include <string>

#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	void OpenDoor();
	void CloseDoor();

	UPROPERTY(VisibleAnywhere)
		float OpenAngle = 80.0f;
	
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;


	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;

	AActor* Owner = nullptr;
	float Opentime;

	bool doorOpened = false;

	//Return total mass in Kg
	float GetTotalMassOfActorsOnPlate();

};
