// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();


	if (PressurePlate != nullptr)
		PressurePlate->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OpenDoor);
	else
		UE_LOG(LogTemp, Error, TEXT("PressurePlateNull"));

	if (PressurePlate != nullptr)
		PressurePlate->OnComponentEndOverlap.AddDynamic(this, &ADoor::CloseDoor);
	else
		UE_LOG(LogTemp, Error, TEXT("PressurePlateNull"));

	DoorPosX = GetActorLocation().X;
	DoorPasY = GetActorLocation().Y;

}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsOverlapping)
	{
		FVector V;
		float Pos = GetActorLocation().Z;
		V.Z = FMath::Lerp(Pos, OpenZ, 0.8*DeltaTime);
		SetActorRelativeLocation(FVector(DoorPosX, DoorPasY, V.Z), true, nullptr, ETeleportType::None);
	}
	else
	{
		FVector V;
		float Pos = GetActorLocation().Z;
		V.Z = FMath::Lerp(Pos, CloseZ, 0.8 * DeltaTime);
		SetActorRelativeLocation(FVector(DoorPosX, DoorPasY, V.Z), true, nullptr, ETeleportType::None);
	}
	
}

void ADoor::OpenDoor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IsOverlapping = true;
}

void ADoor::CloseDoor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	IsOverlapping = false;
}

