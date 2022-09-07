// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponents.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MON_API UCombatComponents : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponents();	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	friend class AM9Character;

	void EquipWeapon(class AWeapon* WeaponToEquip);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	class AM9Character* Character;
	class AWeapon* EquippedWeapon;
	

public:	

		
};
