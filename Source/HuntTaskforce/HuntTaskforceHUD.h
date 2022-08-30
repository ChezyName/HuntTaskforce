// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HuntTaskforceHUD.generated.h"

UCLASS()
class AHuntTaskforceHUD : public AHUD
{
	GENERATED_BODY()

public:
	AHuntTaskforceHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

