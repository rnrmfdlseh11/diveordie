// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRock.h"

// Sets default values
AMyRock::AMyRock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Rock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ROCK"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>SM(TEXT("/Script/Engine.StaticMesh'/Game/StaticMesh/Rock.Rock'"));

	if (SM.Succeeded())
	{
		Rock->SetStaticMesh(SM.Object);
	}
}

// Called when the game starts or when spawned
void AMyRock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

