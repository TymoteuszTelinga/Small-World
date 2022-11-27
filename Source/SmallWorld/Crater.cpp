// Fill out your copyright notice in the Description page of Project Settings.


#include "Crater.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GravityComponent.h"

// Sets default values
ACrater::ACrater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Box"));
	CapsuleComponent->AttachTo(RootComponent);

	GravityCompnent = CreateDefaultSubobject<UGravityComponent>(TEXT("Gravity"));

}

// Called when the game starts or when spawned
void ACrater::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(LiveTime);
	
}
