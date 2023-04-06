// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SeaWeed.generated.h"

UCLASS()
class DIVEORDIE_API ASeaWeed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASeaWeed();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* capsule;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
