// Fill out your copyright notice in the Description page of Project Settings.


#include "DiveOrDieCharacter.h"
#include "DiveCharacterController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
ADiveOrDieCharacter::ADiveOrDieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()-> SetCollisionProfileName(TEXT("CharacterMesh"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));

	BaseTurnRate = 40.0f;
	BaseLookUpRate = 40.0f;

	_fMaxHP = 400.0f;
	_fCurrentHP = _fMaxHP;
	_fMaxOxygen = 500.0f;
	_fCurrentOxygen = _fMaxOxygen;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SOLDIER_SK(TEXT("/Game/Asset/Character/Soldier_T_Pose_.Soldier_T_Pose_"));
	if (SOLDIER_SK.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SOLDIER_SK.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> SOLDIER_ANIM(TEXT("/Game/Asset/Animation/CharacterAnim.CharacterAnim"));
	if (SOLDIER_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(SOLDIER_ANIM.Class);
	}

}
void ADiveOrDieCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ADiveOrDieCharacter::UnPossessed()
{
	Super::UnPossessed();
}

void ADiveOrDieCharacter::SetEnableInput(bool canMove, bool canTurn)
{
	_bCanMove = canMove;
	_bCanTurn = canTurn;
}
void ADiveOrDieCharacter::UpdateScore(int Points)
{
	_iScore += Points;
}

void ADiveOrDieCharacter::SlowDown()
{
	GetCharacterMovement()->MaxSwimSpeed = 200.0f;
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
		GetCharacterMovement()->MaxSwimSpeed = 700.0f;
		}, 1, 0, 4);
}

void ADiveOrDieCharacter::ReceiveAnyDamage(float damage)
{
	_fCurrentHP-= damage;
	if (_fCurrentHP < 0)
		_fCurrentHP = 0;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particles, GetActorTransform(), true, EPSCPoolMethod::None, true);
	if (_fCurrentHP == 0)
	{
		Destroy();
		ADiveCharacterController* controller = Cast<ADiveCharacterController>(GetController());
		controller->TimeLimit = 1;
	}
}

float ADiveOrDieCharacter::GetMaxHP()
{
	return _fMaxHP;
}

float ADiveOrDieCharacter::GetCurrentHP()
{
	return _fCurrentHP;
}

float ADiveOrDieCharacter::GetMaxOxygen()
{
	return _fMaxOxygen;
}

float ADiveOrDieCharacter::GetCurrentOxygen()
{
	return _fCurrentOxygen;
}
// Called when the game starts or when spawned
void ADiveOrDieCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxSwimSpeed = 700.0f;
}

void ADiveOrDieCharacter::MoveForward(float Value)
{
	if (!_bCanMove) return;
	
	if ((Controller != NULL) && (Value != 0.0f))
	{
		if (_bOnSwim)
		{
			AddMovementInput(FollowCamera->GetForwardVector(), Value);
		}
		else
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}
void ADiveOrDieCharacter::MoveRight(float Value)
{
	if (!_bCanMove) return;

	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ADiveOrDieCharacter::TurnAtRate(float Rate)
{
	if (!_bCanTurn) return;

	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADiveOrDieCharacter::LookUpAtRate(float Rate)
{
	if (!_bCanTurn) return;

	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Called every frame
void ADiveOrDieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector velocity = GetCharacterMovement()->Velocity;
	velocity.Z = 0;
	_fGroundSpeed = velocity.Length();

	if (GetVelocity().Size() > 0)
		_bOnMove = true;
	else
		_bOnMove = false;

	if (!_bOnJump && GetCharacterMovement()->IsFalling())
		_bOnJump = true;
	else if (_bOnJump && !GetCharacterMovement()->IsFalling())
		_bOnJump = false;

}


// Called to bind functionality to input
void ADiveOrDieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("UpDown", this, &ADiveOrDieCharacter::MoveForward);
	InputComponent->BindAxis("LeftRight", this, &ADiveOrDieCharacter::MoveRight);
	InputComponent->BindAxis("Yaw", this, &ADiveOrDieCharacter::TurnAtRate);
	InputComponent->BindAxis("Pitch", this, &ADiveOrDieCharacter::LookUpAtRate);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

