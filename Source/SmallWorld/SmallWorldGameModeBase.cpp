// Copyright Epic Games, Inc. All Rights Reserved.


#include "SmallWorldGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "CarController.h"
#include "SmallGameInstance.h"
#include "Planet.h"

void ASmallWorldGameModeBase::BeginPlay() 
{
    PlayerRef = Cast<ACarController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
    PlanetRef  = Cast<APlanet>(UGameplayStatics::GetActorOfClass(GetWorld(),APlanet::StaticClass()));
}

void ASmallWorldGameModeBase::EndGame() 
{
    if(PlayerRef)
    {
        PlayerRef->GameHasEnded(PlayerRef->GetPawn(),true);
    }

    if(PlanetRef)
    {
        PlanetRef->SetCanShrink(false);
    }
}

void ASmallWorldGameModeBase::StartGame() 
{
    if(PlanetRef)
    {
        PlanetRef->SetCanShrink(true);
    }

    if (PlayerRef)
    {
        PlayerRef->Start();
    }
}


