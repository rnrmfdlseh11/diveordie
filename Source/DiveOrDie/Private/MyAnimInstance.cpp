// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

UMyAnimInstance::UMyAnimInstance() {
	Speed = 0.0f;
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//Super::NativeUpdateAnimation(DeltaSeconds);

	//auto Pawn = TryGetPawnOwner();
	//if (::IsValid(Pawn))
	//{
	//	Speed = Pawn->GetVelocity().Size();
	//	auto Character = Cast<ACharacter>(Pawn);
	//	if (Character)
	//	{
	//		//IsOnAir = Character->GetMovementComponent()->IsFalling();
	//	}
	//}
}
