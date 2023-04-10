// Fill out your copyright notice in the Description page of Project Settings.


#include "WarShip_Projectile.h"
#include "DiveOrDie/InGame/Character/DiveCharacter.h"

// Sets default values
AWarShip_Projectile::AWarShip_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILECOMP"));

	box->SetCollisionProfileName("Projectile");
	box->SetBoxExtent(FVector(125.0f, 15.0f, 15.0f));
	
	mesh->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	mesh->SetRelativeLocation(FVector(-105.0f, 0.0f, 0.0f));
	mesh->SetRelativeScale3D(FVector(100.0f, 100.0f, 100.0f));
	mesh->SetCollisionProfileName("NoCollision");

	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PROJECTILE_MESH(TEXT("/Game/Meshes/bullet.bullet"));
    if (PROJECTILE_MESH.Succeeded())
    {
	    mesh->SetStaticMesh(PROJECTILE_MESH.Object);
    }
	
	RootComponent = box;
	mesh->SetupAttachment(RootComponent);

	ProjectileMovementComp->InitialSpeed = 1.0f;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;
	
	ProjectileMovementComp->Velocity = ProjectileMovementComp->Velocity * 1000.0f;
	box->OnComponentHit.AddDynamic(this, &AWarShip_Projectile::OnComponentHit);

}

// Called when the game starts or when spawned
void AWarShip_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWarShip_Projectile::SetBulletStat(float damage, float speed)
{
	_damage = damage;
	_speed = speed;
	ProjectileMovementComp->Velocity = ProjectileMovementComp->Velocity * _speed;
}

void AWarShip_Projectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ADiveCharacter* character = Cast<ADiveCharacter>(OtherActor);
	if (character)
	{
		character->ReceiveAnyDamage(_damage);
		Destroy();
	}
}

