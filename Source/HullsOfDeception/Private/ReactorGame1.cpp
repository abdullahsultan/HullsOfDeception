// Fill out your copyright notice in the Description page of Project Settings.


#include "ReactorGame1.h"

#include "Components/CapsuleComponent.h"
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
	Cast <AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh()->SetVisibility(true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 1.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	this->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	IsCompleted = true;
	IItem::Execute_AtEnd(this);
}

void AReactorGame1::SetButtonOnOff()
{
	FHitResult Hit;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (Hit.GetComponent()->ComponentHasTag("Button"))
	{
		if(Hit.GetComponent()->GetRelativeLocation().Y >= 8.0f && Hit.GetComponent()->GetRelativeLocation().Y <= 9.5f)
		{
			Hit.GetComponent()->SetRelativeLocation(FVector(Hit.GetComponent()->GetRelativeLocation().X, 13.0f, 19.0f), false, nullptr, ETeleportType::None);
		}
		else if(Hit.GetComponent()->GetRelativeLocation().Y >= 12.0f && Hit.GetComponent()->GetRelativeLocation().Y <= 13.5f)
		{
			Hit.GetComponent()->SetRelativeLocation(FVector(Hit.GetComponent()->GetRelativeLocation().X, 9.0f, 21.0f), false, nullptr, ETeleportType::None);
		}

		Check();
	}
}

void AReactorGame1::Check()
{
	for (int X = 0; X < ArrayOfSwitches.Num(); X++)
	{
		if (!ButtonToPush.Contains(X) && ArrayOfSwitches[X]->GetRelativeLocation().Y >= 8.0f && ArrayOfSwitches[X]->GetRelativeLocation().Y <= 9.5f)
		{
			return;
		}
	}
	for (int X = 0; X < ButtonToPush.Num(); X++)
	{
		if(ArrayOfSwitches[ButtonToPush[X]]->GetRelativeLocation().Y >= 12.0f && ArrayOfSwitches[ButtonToPush[X]]->GetRelativeLocation().Y <= 13.5f)
			return;
	}
			TaskCompleted();
}

void AReactorGame1::SomeThingsToDo()
{
	for (int x = 0; x < 4; )
	{
		int32 temp = FMath::RandRange(0, 10);
		if (!ButtonToPush.Contains(temp))
		{
			ButtonToPush.Add(temp);
			x++;
		}
	}

	for (int x = 0; x < ButtonToPush.Num(); x++)
	{
		if (ButtonToPush[x] < ArrayOfLights.Num())
		{
			if (ArrayOfLights[ButtonToPush[x]])
				ArrayOfLights[ButtonToPush[x]]->SetScalarParameterValueOnMaterials("Brighness", 50.0f);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("LightsArray out of bounds"));
	}

	for (int x = 0; x < ButtonToPush.Num(); x++)
	{
		UE_LOG(LogTemp, Warning, TEXT("BBB : %d"), ButtonToPush[x]);
	}
}
