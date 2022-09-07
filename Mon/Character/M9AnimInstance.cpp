// Fill out your copyright notice in the Description page of Project Settings.


#include "M9AnimInstance.h"
#include "M9Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UM9AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	M9Character = Cast<AM9Character>(TryGetPawnOwner());
}


void UM9AnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (M9Character == nullptr)
	{
		M9Character = Cast<AM9Character>(TryGetPawnOwner());
	}
	if (M9Character == nullptr) return;

	FVector Velocity = M9Character->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = M9Character->GetCharacterMovement()->IsFalling();

	bIsAcceleration = M9Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

}
