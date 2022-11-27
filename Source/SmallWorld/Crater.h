// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Crater.generated.h"

class UGravityComponent;
class UCapsuleComponent;

UCLASS()
class SMALLWORLD_API ACrater : public AActor
{
	GENERATED_BODY()
protected:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true") )
	UStaticMeshComponent *Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true") )
	UCapsuleComponent *CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true") )
	UGravityComponent *GravityCompnent;
	//Variabels
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables", meta = (AllowPrivateAccess = "true") )
	float LiveTime = 3.f;
	
public:	
	// Sets default values for this actor's properties
	ACrater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
