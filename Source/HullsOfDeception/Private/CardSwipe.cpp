// Fill out your copyright notice in the Description page of Project Settings.


#include "CardSwipe.h"

#include "HullsOfDeception/HullsOfDeceptionCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACardSwipe::ACardSwipe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACardSwipe::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox = FindComponentByClass<UBoxComponent>();

	if (CollisionBox)
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACardSwipe::Overlapped);
	else
		UE_LOG(LogTemp, Error, TEXT("CollisionBox Null"));

	if (CollisionBox)
		CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ACardSwipe::Away);
	else
		UE_LOG(LogTemp, Error, TEXT("CollisionBox Null"));
}

// Called every frame
void ACardSwipe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACardSwipe::Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->IsInteracting = true;
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->InteractingObjectActor = this;
}

void ACardSwipe::Away(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->IsInteracting = false;
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->InteractingObjectActor = nullptr;
}

void ACardSwipe::OP()
{
	Cast <AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh()->SetVisibility(false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(this, 1.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	this->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Input = FindComponentByClass<UInputComponent>();
	if (Input)
	{
		Input->BindAction("LeftMouseClick", IE_Pressed, this, &ACardSwipe::SetCard);
		Input->BindAction("LeftMouseClick", IE_Released, this, &ACardSwipe::ResetCard);
		Input->BindAxis("Turn", this, &ACardSwipe::MoveCard);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Input is Null"));
}

void ACardSwipe::TaskCompleted()
{
	Cast <AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh()->SetVisibility(true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 1.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	this->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

}

void ACardSwipe::SetCard()
{
	UE_LOG(LogTemp, Warning, TEXT("%d"), GetWorld()->GetRealTimeSeconds());
	FHitResult Hit;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, true, Hit);
	if(Hit.Component == CardMesh)
		CanMoveCard = true;

	GetWorld()->GetTimerManager().SetTimer(TimeHandler, this, &ACardSwipe::SecondCount, 1.0f, true, false);
}

void ACardSwipe::ResetCard()
{
	GetWorld()->GetTimerManager().ClearTimer(TimeHandler); Sec = 0.0f;
	CanMoveCard = false;
	CardMesh->SetRelativeLocation(FVector(CardMesh->GetRelativeLocation().X, 19.0f, CardMesh->GetRelativeLocation().Z), false, nullptr, ETeleportType::None);
}

void ACardSwipe::MoveCard(float X)
{
	float Y;
	if(CanMoveCard)
	{
		if(X>0)
		{
			Y = (CardMesh->GetRelativeLocation().Y - X) ;
			Y =FMath::Clamp(Y,-19.0f, 19.0f);
			CardMesh->SetRelativeLocation(FVector(CardMesh->GetRelativeLocation().X, Y, CardMesh->GetRelativeLocation().Z), false, nullptr, ETeleportType::None);
		}

		else if (X < 0)
		{
			Y = (CardMesh->GetRelativeLocation().Y - X);
			Y = FMath::Clamp(Y, -19.0f, 19.0f);

			CardMesh->SetRelativeLocation(FVector(CardMesh->GetRelativeLocation().X, Y, CardMesh->GetRelativeLocation().Z), false, nullptr, ETeleportType::None);
		}
	}
	if (Y == -19.0f)
	{
		CheckWin();
	}
}

void ACardSwipe::SecondCount()
{
	Sec++;
	UE_LOG(LogTemp, Warning, TEXT("Sec %f"), Sec);
}

void ACardSwipe::CheckWin()
{
	GetWorld()->GetTimerManager().ClearTimer(TimeHandler);
	if (Sec > 2.5f && Sec < 4.5f)
	{
		CardMesh->SetMobility(EComponentMobility::Static);
		IsCompleted = true;
		IItem::Execute_Won(this);
		TaskCompleted();
	}
	else if(Sec < 2.5f)
	{
		IItem::Execute_TooFast(this);
		ResetCard();
	}
	else if(Sec >4.5f)
	{
		IItem::Execute_TooSlow(this);
		ResetCard();
	}
}

