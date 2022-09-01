// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanCharacter.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"

bool AHumanCharacter::DoTrace(FHitResult* RV_Hit, FCollisionQueryParams* RV_TraceParams)
{
	if (Controller == NULL) // access the controller, make sure we have one
		{
		return false;
		}

	// get the camera transform
	FVector CameraLoc;
	FRotator CameraRot;
	GetActorEyesViewPoint(CameraLoc, CameraRot);

	FVector Start = CameraLoc;
	// you need to add a uproperty to the header file for a float PlayerInteractionDistance
	FVector End = CameraLoc + (CameraRot.Vector() * 25000);

	RV_TraceParams->bTraceComplex = true;
	//RV_TraceParams->bTraceAsyncScene = true;
	RV_TraceParams->bReturnPhysicalMaterial = true;

	//  do the line trace
	bool DidTrace = GetWorld()->LineTraceSingleByChannel(
		*RV_Hit,		//result
		Start,		//start
		End,		//end
		ECC_Pawn,	//collision channel
		*RV_TraceParams
		);

	return DidTrace;
}

void AHumanCharacter::FireShot_Implementation(){
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,  GetName() + " Is Trying To Fire A Shot.");
	
	FHitResult RV_Hit(ForceInit);
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.AddIgnoredActor(this);
	DoTrace(&RV_Hit, &RV_TraceParams);

	//Debug / Testing
	if(RV_Hit.Actor != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,GetName() + " has shot " + RV_Hit.Actor->GetName());
		DrawDebugLine(GetWorld(),RV_Hit.TraceStart,RV_Hit.TraceEnd,FColor::Red,false,5);
		DrawDebugBox(GetWorld(),RV_Hit.ImpactPoint,FVector(3,3,3),FColor::Red,false,5);
	}
}
void AHumanCharacter::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	//move flashlight for clients
	if(HasAuthority() && Flashlight != nullptr)
	{
		FRotator relRot = Flashlight->GetRelativeRotation();
		float pitch = GetControlRotation().Pitch;
		if(pitch <= 338 && pitch >= 270)
		{
			pitch = 338;
		}
		else if(pitch <= 90 && pitch >= 27)
		{
			pitch = 27;
		}
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,GetName() + "'s Pitch: '" + FString::SanitizeFloat(GetControlRotation().Pitch));
		Flashlight->SetRelativeRotation(FRotator(pitch,relRot.Roll,relRot.Yaw));
	}
}

void AHumanCharacter::BeginPlay()
{
	Super::BeginPlay();
	Flashlight = (USpotLightComponent*) GetComponentByClass(USpotLightComponent::StaticClass());
	FPSCam = (UCameraComponent*) GetComponentByClass(UCameraComponent::StaticClass());
}

void AHumanCharacter::onAttack()
{
	//Attack / LMB
	FireShot_Implementation();
	Super::onAttack();
}

void AHumanCharacter::onStart()
{
	Super::onStart();
}

void AHumanCharacter::toggleLight_Implementation()
{
	if(Flashlight != nullptr)
	{
		Flashlight->SetVisibility(!Flashlight->IsVisible());
	}
}

void AHumanCharacter::onAbility()
{
	//Ability / F
	toggleLight();
	Super::onAbility();
}