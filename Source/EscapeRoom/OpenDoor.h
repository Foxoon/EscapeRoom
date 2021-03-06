// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include <string>

#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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
	
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OpenDoorRequest;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent CloseDoorRequest;
private:
	void OpenDoor();
	void CloseDoor();

	
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	AActor* Owner = nullptr;
	float Opentime;

	bool doorOpened = false;

	//Return total mass in Kg
	float GetTotalMassOfActorsOnPlate();

};
