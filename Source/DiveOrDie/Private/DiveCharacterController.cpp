// Fill out your copyright notice in the Description page of Project Settings.


#include "DiveCharacterController.h"

void ADiveCharacterController::StartSwimming()
{
	ADiveOrDieCharacter* player = Cast<ADiveOrDieCharacter>(GetPawn());
	player->Jump();
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, [this, player]() {
		player->GetCharacterMovement()->UpdatedPrimitive->GetPhysicsVolume()->bWaterVolume = true;
	Swimming = true;
	player->GetCapsuleComponent()->SetCapsuleHalfHeight(50, 1);
		}, 1, 0, 1);

}

void ADiveCharacterController::StopSwimming()
{
	Swimming = false;
	ADiveOrDieCharacter* player = Cast<ADiveOrDieCharacter>(GetPawn());
	player->GetCharacterMovement()->UpdatedPrimitive->GetPhysicsVolume()->bWaterVolume = false;
	player->GetCapsuleComponent()->SetCapsuleHalfHeight(90, 1);
}

void ADiveCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("UpDown", this, &ADiveCharacterController::UpDown);
	InputComponent->BindAxis("LeftRight", this, &ADiveCharacterController::LeftRight);
	InputComponent->BindAxis("Pitch", this, &ADiveCharacterController::Pitch);
	InputComponent->BindAxis("Yaw", this, &ADiveCharacterController::Yaw);
}

void ADiveCharacterController::UpDown(float value)
{
	GetPawn()->AddMovementInput(GetControlRotation().Vector(), value, 0);
}

void ADiveCharacterController::LeftRight(float value)
{
	FRotator rotation = GetControlRotation();
	GetPawn()->AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y), value, 0);
}

void ADiveCharacterController::Pitch(float value)
{
	AddPitchInput(TurnRate * GetWorld()->GetDeltaSeconds() * value);
}

void ADiveCharacterController::Yaw(float value)
{
	AddYawInput(TurnRate * GetWorld()->GetDeltaSeconds() * value);
}
