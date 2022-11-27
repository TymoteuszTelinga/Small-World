// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Meteor.h"

// Sets default values
APlanet::APlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	bCanShrink = false;
	radiusInUnits = radiusInMeters*100;
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();

	// FTimerHandle Handle;
	// GetWorldTimerManager().SetTimer(Handle,this,&APlanet::SpawnMeteor,SpawnRate,true);
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (radiusInMeters > 3.f && bCanShrink)
	{
		radiusInMeters-=DeltaTime*ShrinkingSpeed;
	}
	SetPlanetSize();

}

void APlanet::OnConstruction(const FTransform& Transform) 
{
	radiusInUnits = radiusInMeters*100;

	FVector Origin,Box;
	float radius;
	Mesh->SetWorldScale3D( FVector(1,1,1) );
	UKismetSystemLibrary::GetComponentBounds(Mesh, Origin, Box, radius);

	FVector NewScale(radiusInUnits/Box.X);
	Mesh->SetWorldScale3D(NewScale);

}

void APlanet::SetPlanetSize() 
{
	radiusInUnits = radiusInMeters*100;
	FVector newScale(radiusInMeters);
	Mesh->SetWorldScale3D(newScale);
}

void APlanet::SpawnMeteor() 
{
	if (MeteorClass)
	{
		FVector Location = UKismetMathLibrary::RandomUnitVector();
		Location*=(radiusInUnits+1200.f);
		Location+=GetActorLocation();
		FRotator Rotacion = UKismetMathLibrary::FindLookAtRotation(Location,GetActorLocation());
		GetWorld()->SpawnActor<AMeteor>(MeteorClass,Location,Rotacion);
	}
}

void APlanet::GetSurfaceLocationAndNormalAt(const FVector Location, FVector &SurfaceLocation, FVector &SurfaceNormal) const
{
	SurfaceNormal = Location - GetActorLocation();
	UKismetMathLibrary::Vector_Normalize(SurfaceNormal);
	SurfaceLocation = SurfaceNormal*radiusInUnits;
	SurfaceLocation += GetActorLocation();
}

void APlanet::SetCanShrink(bool newState) 
{
	bCanShrink = newState;
	if(bCanShrink)
	{
		GetWorldTimerManager().SetTimer(Handle,this,&APlanet::SpawnMeteor,SpawnRate,true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(Handle);
	}
	
}

float APlanet::GetPlanetSize() const
{
	return radiusInUnits;
}
