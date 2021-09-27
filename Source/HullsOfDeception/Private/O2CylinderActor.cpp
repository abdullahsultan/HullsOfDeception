// Fill out your copyright notice in the Description page of Project Settings.


#include "O2CylinderActor.h"
#include "../HullsOfDeceptionCharacter.h"

// Sets default values
AO2CylinderActor::AO2CylinderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AO2CylinderActor::BeginPlay()
{
	Super::BeginPlay();

	if(BoxCollision)
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AO2CylinderActor::Interact);
	else
		UE_LOG(LogTemp, Error, TEXT("BoxCollision is Null"));
	if (BoxCollision)
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AO2CylinderActor::Leave);
	else
		UE_LOG(LogTemp, Error, TEXT("BoxCollision is Null"));

}

// Called every frame
void AO2CylinderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AO2CylinderActor::IncrementO2()
{
	O2++;
}

void AO2CylinderActor::DecrementO2()
{
	O2--;
}

void AO2CylinderActor::Interact(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->IsInteracting = true;
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->InteractingObjectActor = this;
}

void AO2CylinderActor::Leave(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->IsInteracting = false;
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->InteractingObjectActor = nullptr;
}

