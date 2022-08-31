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

	virtual void onAttack() override;
	virtual void onStart() override;
	virtual void onAbility() override;
};
