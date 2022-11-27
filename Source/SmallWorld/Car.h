// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Car.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class UGravityComponent;
class USmallGameInstance;

UCLASS()
class SMALLWORLD_API ACar : public APawn
{
	GENERATED_BODY()
private:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true") )
	UStaticMeshComponent *Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true") )	
	USpringArmComponent *SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true") )
	UCameraComponent *Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true") )
	UBoxComponent *Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true") )
	UGravityComponent *GravityCompnent;

	//Variabels
	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem *DeathParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables", meta = (AllowPrivateAccess = "true") )
	float MovementSpeed = 1200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables", meta = (AllowPrivateAccess = "true") )
	float RotateAmount = 1.2f;

	bool bCanMove = true;
	float deltaSeconds;
	float cameraDistance;
	USmallGameInstance*  GameInstanceRef;

public:
	// Sets default values for this pawn's properties
	ACar();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ColectCoin(int value) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void Rotate(float value);
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
