// Fill out your copyright notice in the Description page of Project Settings.


#include "Net.h"
#include "DiveOrDieCharacter.h"

// Sets default values
ANet::ANet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = capsule;
	capsule->SetCapsuleHalfHeight(110);
	capsule->SetCapsuleRadius(80);

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	mesh->SetCollisionProfileName("Object");
	capsule->SetCollisionProfileName("OverlapAllDynamic");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> NET_MESH(TEXT(""));
	if (NET_MESH.Succeeded())
	{
		mesh->SetStaticMesh(NET_MESH.Object);
	}

	capsule->OnComponentBeginOverlap.AddDynamic(this, &ANet::OnOverlapBegin);

}

void ANet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	LOG_SCREEN("Overlap Net");
	ADiveOrDieCharacter* character = Cast<ADiveOrDieCharacter>(OtherActor);
	if (character)
	{
		character->Restraint(10.0f);
	}
}

// Called when the game starts or when spawned
void ANet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

