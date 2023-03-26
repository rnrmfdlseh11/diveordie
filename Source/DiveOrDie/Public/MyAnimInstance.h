// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DIVEORDIE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMyAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsOnAir;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool isSwim;

};
