// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldRing.h"

// Sets default values
AGoldRing::AGoldRing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = capsule;
	capsule->SetCapsuleHalfHeight(80);
	capsule->SetCapsuleRadius(70);


	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	movement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating movement"));
	movement->RotationRate = FRotator(180, 0, 0);


	FScriptDelegate dele;
	dele.BindUFunction(this, "OnHit");

	mesh->OnComponentHit.Add(dele);
}

void AGoldRing::OnOverlap(AActor* OtherActor)
{
	ADiveOrDieCharacter* character = Cast<ADiveOrDieCharacter>(OtherActor);
	if (character)
	{
		character->UpdateScore(PointValue);
		UGameplayStatics::PlaySound2D(this, Sound, 1, 1, 0);
		Destroy();
	}
}
// Called when the game starts or when spawned
void AGoldRing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoldRing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

