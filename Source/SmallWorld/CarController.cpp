// Fill out your copyright notice in the Description page of Project Settings.


#include "CarController.h"
#include "Blueprint/UserWidget.h"
#include "SmallWorldGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void ACarController::BeginPlay() 
{
    Super::BeginPlay();

    StartScrean = CreateWidget(this, StartScreenClass);
    if (StartScrean != NULL)
    {
        StartScrean->AddToViewport();
    }
    bShowMouseCursor = true;
    GetPawn()->DisableInput(this);
    SetInputMode(FInputModeGameOnly());
}

void ACarController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUD->RemoveFromViewport();

    UUserWidget *EndScrean = CreateWidget(this, EndScreenClass);
    if (EndScrean != NULL)
    {
        EndScrean->AddToViewport();
    }

    GetPawn()->DisableInput(this);
    bShowMouseCursor = true;
    //SetInputMode(FInputModeUIOnly());
}

void ACarController::Start() 
{
    StartScrean->RemoveFromViewport();

    HUD = CreateWidget(this, HUDClass);
    if (HUD != NULL)
    {
        HUD->AddToViewport();
    }
    GetPawn()->EnableInput(this);
    bShowMouseCursor = false;
}
