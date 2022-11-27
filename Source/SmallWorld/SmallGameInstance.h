// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SmallGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SMALLWORLD_API USmallGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int Money = 0;

};
