// Fill out your copyright notice in the Description page of Project Settings.

#include "Coin.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "GravityComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Car.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetupAttachment(Mesh);

	GravityCompnent = CreateDefaultSubobject<UGravityComponent>(TEXT("Gravity"));

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnCapsuleBeginOverlap);
	
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Mesh->AddLocalRotation(FRotator(RotacionSpeed*DeltaTime,0,0));

}

void ACoin::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACar* CarRef = Cast<ACar>(OtherActor);
	if(CarRef)
	{
		CarRef->ColectCoin(1);
		FVector Location = UKismetMathLibrary::RandomUnitVector();
		Location*=(10000.f);
		Location+=GravityCompnent->GetPlanetLocation();
		GetWorld()->SpawnActor<ACoin>(CoinClass,Location,FRotator(0.f,0.f,0.f));
		Destroy();
	}
}

