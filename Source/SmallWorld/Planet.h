// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Planet.generated.h"

class AMeteor;

UCLASS()
class SMALLWORLD_API APlanet : public AActor
{
	GENERATED_BODY()
private:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true") )
	UStaticMeshComponent *Mesh;
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defoult", meta = (AllowPrivateAccess = "true") )
	float radiusInMeters = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defoult", meta = (AllowPrivateAccess = "true") )
	float SpawnRate = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defoult", meta = (AllowPrivateAccess = "true") )
	float ShrinkingSpeed = 0.3f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defoult", meta = (AllowPrivateAccess = "true") )
	TSubclassOf<AMeteor> MeteorClass;

	float radiusInUnits;
	bool bCanShrink;
	FTimerHandle Handle;
	//Funcions
	void SetPlanetSize();
	void SpawnMeteor();
	
public:	
	// Sets default values for this actor's properties
	APlanet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	void GetSurfaceLocationAndNormalAt(const FVector Location, FVector &SurfaceLocation, FVector &SurfaceNormal) const;
	void SetCanShrink(bool newState);
	float GetPlanetSize() const;

};
