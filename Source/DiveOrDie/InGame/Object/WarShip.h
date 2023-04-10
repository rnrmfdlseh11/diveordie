// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../game.h"
#include "GameFramework/Pawn.h"
#include "BuoyancyComponent.h"
#include "DiveOrDie/InGame/Character/DiveCharacter.h"
#include "WarShip.generated.h"

UCLASS()
class GAME_API AWarShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWarShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MoveTarget();

	void Shoot();

	void ShootReload();

	bool bCanShoot = true;
	FTimerHandle ShootTimer;

	bool bOnMove = false;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UBuoyancyComponent* buoyancy;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	ADiveCharacter* Target;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
