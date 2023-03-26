// Fill out your copyright notice in the Description page of Project Settings.


#include "DiveOrDieCharacter.h"
#include "DiveCharacterController.h"

// Sets default values
ADiveOrDieCharacter::ADiveOrDieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ADiveOrDieCharacter::UpdateScore(int Points)
{
	Score += Points;
}

void ADiveOrDieCharacter::SlowDown()
{
	GetCharacterMovement()->MaxSwimSpeed = 200;
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
		GetCharacterMovement()->MaxSwimSpeed = 400;
		}, 1, 0, 4);
}

void ADiveOrDieCharacter::ReceiveAnyDamage(float damage)
{
	CurrentHealth -= damage;
	if (CurrentHealth < 0)
		CurrentHealth = 0;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particles, GetActorTransform(), true, EPSCPoolMethod::None, true);
	if (CurrentHealth == 0)
	{
		Destroy();
		ADiveCharacterController* controller = Cast<ADiveCharacterController>(GetController());
		controller->TimeLimit = 1;
	}
}

// Called when the game starts or when spawned
void ADiveOrDieCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;
}

// Called every frame
void ADiveOrDieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector velocity = GetCharacterMovement()->Velocity;
	velocity.Z = 0;
	GroundSpeed = velocity.Length();

}

// Called to bind functionality to input
void ADiveOrDieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

