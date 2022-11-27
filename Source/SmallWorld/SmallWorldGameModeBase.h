// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SmallWorldGameModeBase.generated.h"

class APlanet;
class ACarController;
/**
 * 
 */
UCLASS()
class SMALLWORLD_API ASmallWorldGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	APlanet *PlanetRef;
	ACarController *PlayerRef;

public:
	void EndGame();
	void StartGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
