// Fill out your copyright notice in the Description page of Project Settings.


#include "Radio.h"
#include "Kismet/GameplayStatics.h"
#include "HullsOfDeception/HullsOfDeceptionCharacter.h"

// Sets default values
ARadio::ARadio()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ARadio::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox = FindComponentByClass<UBoxComponent>();

	if (CollisionBox)
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ARadio::Overlapped);
	else
		UE_LOG(LogTemp, Error, TEXT("CollisionBox Null"));

	if (CollisionBox)
		CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ARadio::Away);
	else
		UE_LOG(LogTemp, Error, TEXT("CollisionBox Null"));
}

// Called every frame
void ARadio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARadio::Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->IsInteracting = true;
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->InteractingObjectActor = this;
}

void ARadio::Away(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex) 
{
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->IsInteracting = false;
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->InteractingObjectActor = nullptr;


}

void ARadio::OP()
{
	Cast <AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh()->SetVisibility(false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(this, 1.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	this->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ARadio::TaskCompleted()
{
	Cast <AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh()->SetVisibility(true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 1.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	this->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	IsCompleted = true;
}



