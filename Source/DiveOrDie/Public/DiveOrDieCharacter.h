// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "DiveOrDieCharacter.generated.h"

class DiveCharacterController;
UCLASS()
class DIVEORDIE_API ADiveOrDieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADiveOrDieCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;

	void SetEnableInput(bool canMove = true, bool canTurn = true);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = Instance, meta = (AllowPrivateAccess = true))
		bool _bCanMove = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = Instance, meta = (AllowPrivateAccess = true))
		bool _bCanTurn = true;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UFUNCTION(BlueprintCallable)
		float GetMaxHP();

	UFUNCTION(BlueprintCallable)
		float GetCurrentHP();

	UFUNCTION(BlueprintCallable)
		float GetMaxOxygen();

	UFUNCTION(BlueprintCallable)
		float GetCurrentOxygen();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = true))
	bool _bOnMove = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = true))
	bool _bOnJump = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = true))
	bool _bOnSwim = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = true))
	int _iScore = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = true))
	float _fMaxHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = true))
	float _fCurrentHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = true))
	float _fGroundSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = true))
	float _fMaxOxygen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = true))
	float _fCurrentOxygen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = true))
	UParticleSystem* particles;

public:
	UFUNCTION(BlueprintCallable)
		void UpdateScore(int Points);

	UFUNCTION(BlueprintCallable)
		void SlowDown();

	void ReceiveAnyDamage(float damage);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
