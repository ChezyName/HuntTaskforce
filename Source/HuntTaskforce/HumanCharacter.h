// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HuntTaskforceCharacter.h"
#include "HumanCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HUNTTASKFORCE_API AHumanCharacter : public AHuntTaskforceCharacter
{
	GENERATED_BODY()

	bool DoTrace(FHitResult* RV_Hit, FCollisionQueryParams* RV_TraceParams);

	UFUNCTION(Server,Reliable)
	void FireShot();

	void Tick(float DeltaSeconds) override;
	void BeginPlay() override;
	
	virtual void onAttack() override;
	virtual void onStart() override;
	virtual void onAbility() override;

	UFUNCTION(Server,Reliable)
	void toggleLight();

	class USpotLightComponent* Flashlight;
	class UCameraComponent* FPSCam;
};
