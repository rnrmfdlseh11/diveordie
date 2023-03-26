// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "DiveOrDieCharacter.generated.h"

UCLASS()
class DIVEORDIE_API ADiveOrDieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADiveOrDieCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* particles;

	UFUNCTION(BlueprintCallable)
		void UpdateScore(int Points);

	UFUNCTION(BlueprintCallable)
		void SlowDown();

	void ReceiveAnyDamage(float damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
