// Copyright Epic Games, Inc. All Rights Reserved.

#include "HuntTaskforceCharacter.h"

#include <string>

#include "HuntTaskforceProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "Components/SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Windows/LiveCodingServer/Public/ILiveCodingServer.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AHuntTaskforceCharacter

//Overriden Virtual Funcs Used by Each Game Character
// IE: Human & Monster
void AHuntTaskforceCharacter::onAttack(){}
void AHuntTaskforceCharacter::onAbility(){}
void AHuntTaskforceCharacter::onStart(){}

void AHuntTaskforceCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//returns if moving backgrounds or forwards
float AHuntTaskforceCharacter::getForwardSpeed()
{
	FVector vel = GetActorRotation().Vector() * GetVelocity();
	if(vel.Y > 0) return 1;
	else if(vel.Y < 0) return -1;
	else return 0;
}

float AHuntTaskforceCharacter::getRightSpeed()
{
	FVector vel = GetActorRotation().Vector() * GetVelocity();
	if(vel.X > 0) return 1;
	else if(vel.X < 0) return -1;
	else return 0;
}

AHuntTaskforceCharacter::AHuntTaskforceCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0,1.75,74.0)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

void AHuntTaskforceCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	localRole = GetLocalRole();

	if (IsLocallyControlled())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, this->GetName() + " ROLE: ");
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,(localRole == ENetRole::ROLE_AutonomousProxy) ? "AUTOPROX" : "N?A");
		//Our own character
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("This is client player"));
		GetMesh()->SetVisibility(false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is server player"));
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHuntTaskforceCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Ability", IE_Pressed, this, &AHuntTaskforceCharacter::onAbility);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHuntTaskforceCharacter::onAttack);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AHuntTaskforceCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHuntTaskforceCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AHuntTaskforceCharacter::MoveForward(float Value)
{
	if (IsLocallyControlled())
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}
void AHuntTaskforceCharacter::MoveRight(float Value)
{
	if (IsLocallyControlled())
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}