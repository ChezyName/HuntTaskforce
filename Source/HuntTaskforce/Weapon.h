// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Weapon.generated.h"

UENUM()
enum class WepType
{
	AR = 0 UMETA(DisplayName="Assult Rifle"),
	SMG = 1 UMETA(DisplayName="SubMachine Gun"),
	LMG = 2 UMETA(DisplayName="LightMachine Gun"),
	DMR = 3 UMETA(DisplayName="Designated Marksman Rifle"),
	SNPR = 4 UMETA(DisplayName="Sniper Rifle"),
};

UENUM()
enum class FModes
{
	Single = 0 UMETA(DisplayName="Single Fire"),
	Burst = 0 UMETA(DisplayName="Burst"),
	Auto = 0 UMETA(DisplayName="Fully Auto"),
};

USTRUCT()
struct FireType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FModes FireMode;

	UPROPERTY(EditAnywhere)
	float Firerate;
};



/**
 * 
 */
UCLASS()
class HUNTTASKFORCE_API UWeapon : public UDataAsset
{
	GENERATED_BODY()

public:
	// Main Properties
	/** The viewmodel of the given weapon, only seen by the local player */
	UPROPERTY(EditAnywhere,Category="MAIN")
	UStaticMeshComponent* Viewmdoel;
	/** The world model of the given weapon, used for global animations, seen by everyone */
	UPROPERTY(EditAnywhere,Category="MAIN")
	UStaticMeshComponent* WeaponModel;
	/** The type of weapon it is, */
	UPROPERTY(EditAnywhere,Category="MAIN")
	WepType WeaponType;


	//Firing / Firing Modes
	/** The speed at which the weapon flys thru the sky */
	UPROPERTY(EditAnywhere,Category="Firing")
	float BulletVelocity = 800;
	/** The list of firing types with the firerate */
	UPROPERTY(EditAnywhere,Category="Firing")
	TArray<FireType> FiringModes;

	//Damage
	/** Headshot Damage */
	UPROPERTY(EditAnywhere,Category="Damage")
	float HeadDamage = 80;
	/** Torso Damage */
	UPROPERTY(EditAnywhere,Category="Damage")
	float TorsoDamage = 50;
	/** Arms & Legs Damage */
	UPROPERTY(EditAnywhere,Category="Damage")
	float ExtremityDamage = 20;
};
