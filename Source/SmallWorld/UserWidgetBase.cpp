// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Planet.h"
#include "SmallWorldGameModeBase.h"
#include "SmallGameInstance.h"
#include "SaveGameData.h"

void UUserWidgetBase::LoadGame() 
{
    USaveGameData *SaveGameInstance = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
    SaveGameInstance = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot"), 0));

    if(SaveGameInstance)
    {
        SmalestPlanet = SaveGameInstance->SmalestPlanet;
    }
}

void UUserWidgetBase::SaveGame() 
{
    USaveGameData *SaveGameInstance = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
    float ValueToSave = getPlanetSize();

    if ( SmalestPlanet > ValueToSave)
    {
        SaveGameInstance->SmalestPlanet = ValueToSave;
    }
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("SaveSlot"), 0);
    //UE_LOG(LogTemp,Warning,TEXT("Hight score %f"),  SaveGameInstance->SmalestPlanet);
}

void UUserWidgetBase::Quit() 
{
    UKismetSystemLibrary::QuitGame(GetWorld(),GetOwningPlayer(),EQuitPreference::Quit,false);
}

void UUserWidgetBase::Restart() 
{
    FString Name = UGameplayStatics::GetCurrentLevelName(GetWorld(),true);
    FName LevelName = FName(Name);
    UGameplayStatics::OpenLevel(GetWorld(),LevelName,true,"");
}

float UUserWidgetBase::getPlanetSize() 
{
    APlanet *PlanetRef  = Cast<APlanet>(UGameplayStatics::GetActorOfClass(GetWorld(),APlanet::StaticClass()));
    if(PlanetRef)
    {
        return PlanetRef->GetPlanetSize()/100;
    }
    return 0.f;
}

void UUserWidgetBase::StartGame()
{
    ASmallWorldGameModeBase *GameModeRef = Cast<ASmallWorldGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if(GameModeRef)
	{
		GameModeRef->StartGame();
	}
}