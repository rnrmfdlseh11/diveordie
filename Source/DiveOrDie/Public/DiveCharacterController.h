// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DiveOrDieCharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PhysicsVolume.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"

#include "DiveCharacterController.generated.h"
/**
 * 
 */
UCLASS()
class DIVEORDIE_API ADiveCharacterController : public APlayerController
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
		void StartSwimming();
	UFUNCTION(BlueprintCallable)
		void StopSwimming();

	virtual void SetupInputComponent() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Swimming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int TimeLimit = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool GameOver;

	void UpDown(float value);
	void LeftRight(float value);
	void Pitch(float value);
	void Yaw(float value);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float TurnRate = 100;

};
