// Fill out your copyright notice in the Description page of Project Settings.


#include "Meteor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Crater.h"

// Sets default values
AMeteor::AMeteor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleTrail"));
	ParticleTrail->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMeteor::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AMeteor::OnCapsuleBeginOverlap);
	
}

// Called every frame
void AMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Direction = Mesh->GetForwardVector();
	Direction*=DeltaTime*MovementSpeed;

	AddActorWorldOffset(Direction);

}


void AMeteor::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) 
{
	if(OtherActor == this)
	{
		return;
	}

	if(!Cast<ACrater>(OtherActor))
	{
		//UE_LOG(LogTemp,Warning,TEXT("CastFailed"));
		if(!bDoOnce)
		{
			//UE_LOG(LogTemp,Warning,TEXT("DoOnce"));
			GetWorld()->SpawnActor<ACrater>(CraterClass, GetActorLocation(), GetActorRotation());
			UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
			bDoOnce = true;
		}
	}

	Destroy();

}
