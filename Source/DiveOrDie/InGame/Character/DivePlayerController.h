// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DiveCharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PhysicsVolume.h"
#include "Engine/World.h"
#include "DivePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API ADivePlayerController : public APlayerController
{
	GENERATED_BODY()


	virtual void SetupInputComponent() override;
};
