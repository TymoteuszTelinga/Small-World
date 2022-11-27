// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetBase.generated.h"

/**
 * 
 */

UCLASS()
class SMALLWORLD_API UUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"));
	float SmalestPlanet = 3.40282e+038;
	UFUNCTION(BlueprintCallable, Category= "Utilitys")
	void SaveGame();
	UFUNCTION(BlueprintCallable, Category= "Utilitys")
	void LoadGame();
	UFUNCTION(BlueprintCallable, Category= "Utilitys")
	void Quit();
	UFUNCTION(BlueprintCallable, Category= "Utilitys")
	void StartGame();
	UFUNCTION(BlueprintCallable, Category= "Utilitys")
	void Restart();
	UFUNCTION(BlueprintCallable, Category= "Utilitys")
	float getPlanetSize();
	
};
