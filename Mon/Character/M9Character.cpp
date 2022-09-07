// Fill out your copyright notice in the Description page of Project Settings.


#include "M9Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "Mon/Weapon/Weapon.h"
#include "Mon/MonComponents/CombatComponents.h"

// Sets default values
AM9Character::AM9Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	HeadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeadWidget"));
	HeadWidget->SetupAttachment(RootComponent);

	Combat = CreateDefaultSubobject<UCombatComponents>(TEXT("CombatComponent"));
	Combat->SetIsReplicated(true);
}

void AM9Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AM9Character, OverlappingWeapon,COND_OwnerOnly);
}


// Called when the game starts or when spawned
void AM9Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AM9Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Define Character Movement function

void AM9Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &AM9Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AM9Character::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AM9Character::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AM9Character::LookUp);

	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &AM9Character::EquipButtonPressed);
}

void AM9Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (Combat)
	{
		Combat->Character = this;
	}

}

void AM9Character::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		// 这是获取的角色前向，不同于控制者前 GetActorForwardVector()

		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void AM9Character::MoveRight(float Value)
{
	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
	AddMovementInput(Direction, Value);
}

void AM9Character::Turn(float value)
{
	AddControllerYawInput(value);
}

void AM9Character::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void AM9Character::EquipButtonPressed()
{
	if (Combat)
	{
		if (HasAuthority())
		{
			Combat->EquipWeapon(OverlappingWeapon);
		}
		else
			ServerEquipButtonPressed();
	}

}

 void AM9Character::ServerEquipButtonPressed_Implementation()
{
	 if (Combat)
	 {
		 Combat->EquipWeapon(OverlappingWeapon);
	 }

}

void AM9Character::SetOverlappingWeapon(AWeapon* Weapon)
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(false);
	}
	OverlappingWeapon = Weapon;
	if (IsLocallyControlled())
	{
		if (OverlappingWeapon)
		{
			OverlappingWeapon->ShowPickupWidget(true);
		}

	}
}

void AM9Character::OnRep_OverlappingWeapon(AWeapon* LastWeapon)
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(true);
	}
	if (LastWeapon)
	{
		LastWeapon->ShowPickupWidget(false);
	}
}









