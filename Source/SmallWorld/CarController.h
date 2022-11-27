// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CarController.generated.h"

class UUserWidget;

UCLASS()
class SMALLWORLD_API ACarController : public APlayerController
{
	GENERATED_BODY()
private:
	//Variables
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> HUDClass;
	UUserWidget *HUD;
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> EndScreenClass;
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> StartScreenClass;
	UUserWidget *StartScrean;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	void Start();

	
};
