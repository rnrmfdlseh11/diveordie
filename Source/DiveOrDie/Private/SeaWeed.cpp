// Fill out your copyright notice in the Description page of Project Settings.


#include "SeaWeed.h"
#include "DiveOrDieCharacter.h"

// Sets default values
ASeaWeed::ASeaWeed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = capsule;
	capsule->SetCapsuleHalfHeight(70.0f);
	capsule->SetCapsuleRadius(40.0f);

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	mesh->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	mesh->SetRelativeLocation(FVector(0.0f, 15.0f, -80.0f));

	mesh->SetCollisionProfileName("Object");
	capsule->SetCollisionProfileName("OverlapAllDynamic");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SEAWEED_SK(TEXT(""));
	if (SEAWEED_SK.Succeeded())
	{
		mesh->SetSkeletalMesh(SEAWEED_SK.Object);
	}

	capsule->OnComponentBeginOverlap.AddDynamic(this, &ASeaWeed::OnOverlapBegin);
}

void ASeaWeeds::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADiveOrDieCharacter* character = Cast<ADiveOrDieCharacter>(OtherActor);
	if (character)
	{
		character->SlowDown(10.0f);
	}
}

// Called when the game starts or when spawned
void ASeaWeed::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASeaWeed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

