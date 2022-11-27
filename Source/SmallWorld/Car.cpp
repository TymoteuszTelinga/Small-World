// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GravityComponent.h"
#include "SmallGameInstance.h"
#include "Crater.h"
#include "SmallWorldGameModeBase.h"

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


	GravityCompnent = CreateDefaultSubobject<UGravityComponent>(TEXT("Gravity"));

}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACar::OnBoxBeginOverlap);
	GameInstanceRef = Cast<USmallGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	cameraDistance = SpringArm->TargetArmLength;
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaSeconds = DeltaTime;

	if(bCanMove)
	{
		FVector Forward = Mesh->GetForwardVector();
		Forward*=DeltaTime*MovementSpeed;
		// SpringArm->TargetArmLength -= 2.0f;
		AddActorWorldOffset(Forward);
	}
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACar::Rotate);

}

void ACar::ColectCoin(int value) const
{
	if (!GameInstanceRef)
	{
		return;
	}

	GameInstanceRef->Money+=value;
	UE_LOG(LogTemp, Warning, TEXT("Colected Coin value: %d"),value);
}

void ACar::Rotate(float value) 
{
	FRotator Rotacion(0,value*RotateAmount*deltaSeconds,0);
	AddActorLocalRotation(Rotacion);
}

void ACar::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) 
{
	// ignoruj wszysko poza kraterami
	if (!Cast<ACrater>(OtherActor))
	{
		return;
	}
	
	ASmallWorldGameModeBase *GameModeRef = Cast<ASmallWorldGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if(GameModeRef)
	{
		GameModeRef->EndGame();
	}
	Mesh->SetVisibility(false,true);
	bCanMove = false;
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
}
