// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Planet.h"

// Sets default values for this component's properties
UGravityComponent::UGravityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGravityComponent::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<APlanet> planet = APlanet::StaticClass();
	AActor *ActorRef = UGameplayStatics::GetActorOfClass(GetWorld(),planet);
	PlanetRef = Cast<APlanet>(ActorRef);
}


// Called every frame
void UGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!PlanetRef)
	{
		return;
	}

	FVector Location,Normal;
	PlanetRef->GetSurfaceLocationAndNormalAt(GetOwner()->GetActorLocation(),Location,Normal);
	FRotator Rotacion = UKismetMathLibrary::MakeRotFromZX(Normal,GetOwner()->GetActorForwardVector());
	GetOwner()->SetActorLocationAndRotation(Location,Rotacion);
}

FVector UGravityComponent::GetPlanetLocation() const
{
	if(!PlanetRef)
	{
		return FVector(0,0,0);
	}
	
	return PlanetRef->GetActorLocation();
}
