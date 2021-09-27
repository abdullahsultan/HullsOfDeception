// Fill out your copyright notice in the Description page of Project Settings.


#include "ReactorGame1.h"
#include "HullsOfDeception/HullsOfDeceptionCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AReactorGame1::AReactorGame1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AReactorGame1::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision = FindComponentByClass<UBoxComponent>();

	if (BoxCollision)
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AReactorGame1::Overlapped);
	else
		UE_LOG(LogTemp, Error, TEXT("CollisionBox Null"));

	if (BoxCollision)
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AReactorGame1::Away);
	else
		UE_LOG(LogTemp, Error, TEXT("CollisionBox Null"));
	
}



void AReactorGame1::Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->IsInteracting = true;
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->InteractingObjectActor = this;
}

void AReactorGame1::Away(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->IsInteracting = false;
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->InteractingObjectActor = nullptr;
}

void AReactorGame1::OP()
{
	Cast <AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh()->SetVisibility(false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(this, 1.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	this->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Input = FindComponentByClass<UInputComponent>();
	if (Input)
	{
		Input->BindAction("LeftMouseClick", IE_Pressed, this, &AReactorGame1::SetButtonOnOff);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Input is Null"));

	SomeThingsToDo();
}

void AReactorGame1::TaskCompleted()
{
}

void AReactorGame1::SetButtonOnOff()
{
	FHitResult Hit;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, true, Hit);

	if (Hit.GetComponent()->ComponentHasTag("Button"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Name %s"), *Hit.GetComponent()->GetRelativeLocation().ToString());
		if(Hit.GetComponent()->GetRelativeLocation().Y == 13.0f)
			Hit.GetComponent()->SetRelativeLocation(FVector(Hit.GetComponent()->GetRelativeLocation().X, 9.0f, 21.0f), true, nullptr, ETeleportType::None);
		else
			Hit.GetComponent()->SetRelativeLocation(FVector(Hit.GetComponent()->GetRelativeLocation().X, 13.0f, 19.0f), true, nullptr, ETeleportType::None);
	}

}

void AReactorGame1::SomeThingsToDo()
{
	for (int x = 0; x < 4; )
	{
		int32 temp = FMath::RandRange(0, 10);
		UE_LOG(LogTemp, Warning, TEXT("UP %d"), x);
		if (!ButtonToPush.Contains(temp))
		{
			ButtonToPush.Add(temp);
			x++;
		}
	}

	for (int x = 0; x < ButtonToPush.Num(); x++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Down %d"), x);
		if (ButtonToPush[x] < ArrayOfLights.Num())
		{
			if (ArrayOfLights[ButtonToPush[x]])
				ArrayOfLights[ButtonToPush[x]]->SetScalarParameterValueOnMaterials("Brighness", 50.0f);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("LightsArray out of bounds"));
	}
}
