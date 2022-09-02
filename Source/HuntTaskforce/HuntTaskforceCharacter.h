// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HuntTaskforceCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class AHuntTaskforceCharacter : public ACharacter
{
	GENERATED_BODY()
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	AHuntTaskforceCharacter();
	
	virtual void BeginPlay();
	ENetRole localRole;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Character")
    USkeletalMeshComponent* CharacterBody;
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	virtual void onAttack();
	virtual void onAbility();
	virtual void onStart();

	void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	float getForwardSpeed();

	UFUNCTION(BlueprintCallable)
	float getRightSpeed();
protected:
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
};

