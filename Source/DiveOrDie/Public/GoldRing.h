// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiveOrDieCharacter.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "GoldRing.generated.h"

UCLASS()
class DIVEORDIE_API AGoldRing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoldRing();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PointValue = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* Sound;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* capsule;

	UPROPERTY(EditAnywhere)
		URotatingMovementComponent* movement;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;
	UFUNCTION(BlueprintCallable)
		void OnOverlap(AActor* OtherActor);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
