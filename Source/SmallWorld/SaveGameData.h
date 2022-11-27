// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameData.generated.h"

/**
 * 
 */
UCLASS()
class SMALLWORLD_API USaveGameData : public USaveGame
{
	GENERATED_BODY()

public:

	USaveGameData();

	UPROPERTY(EditAnywhere)
	float SmalestPlanet;
	UPROPERTY(EditAnywhere)
	float SavedCoins;
	
};
