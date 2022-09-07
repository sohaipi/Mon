// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeadWidget.generated.h"

/**
 * 
 */
UCLASS()
class MON_API UHeadWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY (meta = (BindWidget))
	class UTextBlock* DisplayText;

	void SetDisplayText(FString TextToDisplay);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(APawn* Inpawn);

	//≤‚ ‘œ‘ æΩ«…´√˚◊÷
	/*
	UFUNCTION(BlueprintCallable)
	void ShowPlayerName(APawn* Inpawn);
	*/

protected:
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld*  InWord) override;

};
