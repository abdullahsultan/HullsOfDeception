// Fill out your copyright notice in the Description page of Project Settings.


#include "WireSystem.h"

#include <string>

#include "HullsOfDeception/HullsOfDeceptionCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWireSystem::AWireSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWireSystem::BeginPlay()
{
	Super::BeginPlay();

	InitializeSomeThing();
}

// Called every frame
void AWireSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWireSystem::AttachWire(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OverlappedComp->ComponentHasTag("Brown") && OtherComp->ComponentHasTag("Brown"))
	{
		/*CanMoveBrown = false;*/ OtherComp->SetMobility(EComponentMobility::Static); NoOfWires++;
	}
	else if (OverlappedComp->ComponentHasTag("Green") && OtherComp->ComponentHasTag("Green"))
	{
		/*CanMoveGreen = false;*/ OtherComp->SetMobility(EComponentMobility::Static); NoOfWires++;
	}
	else if (OverlappedComp->ComponentHasTag("Blue") && OtherComp->ComponentHasTag("Blue"))
	{
		/*CanMoveBlue = false;*/ OtherComp->SetMobility(EComponentMobility::Static); NoOfWires++;
	}
	if (OverlappedComp->ComponentHasTag("Red") && OtherComp->ComponentHasTag("Red"))
	{
		/*CanMoveRed = false;*/ OtherComp->SetMobility(EComponentMobility::Static); NoOfWires++;
	}

	if (NoOfWires >= 4)
	{
		IsCompleted = true;
		TaskCompleted();
	}
}


void AWireSystem::DetectWire()
{
	FHitResult Hit;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, true, Hit);

	UE_LOG(LogTemp, Warning, TEXT("Name of Comp: %s"), *Hit.Component->GetName());

	if(Hit.Component->ComponentHasTag("Brown") /*&& CanMoveBrown*/)
	{
		SelectedWire = BrownWire;
		InnitialPosition = SelectedWire->GetRelativeLocation();
	}
	else if(Hit.Component->ComponentHasTag("Green") /*&& CanMoveGreen*/)
	{
		SelectedWire = GreenWire;
		InnitialPosition = SelectedWire->GetRelativeLocation();
	}
	else if (Hit.Component->ComponentHasTag("Red") /*&& CanMoveRed*/)
	{
		SelectedWire = RedWire;
		InnitialPosition = SelectedWire->GetRelativeLocation();
	}
	else if(Hit.Component->ComponentHasTag("Blue") /*&& CanMoveBlue*/)
	{
		SelectedWire = BlueWire;
		InnitialPosition = SelectedWire->GetRelativeLocation();
	}

}



void AWireSystem::MoveWireVertical(float Vertical)
{
	float Z = 0.0f;
	if (SelectedWire)
	Z = SelectedWire->GetRelativeLocation().Z;

	if (Vertical < 0.000f)
		Z = Z + 0.2f;
	else if(Vertical > 0.000f)
		Z = Z - 0.2f;
	
	Z = FMath::Clamp(Z, 10.0f, 25.0F);
	if(SelectedWire)
		SelectedWire->SetRelativeLocation(FVector(SelectedWire->GetRelativeLocation().X, SelectedWire->GetRelativeLocation().Y, Z), false, nullptr, ETeleportType::None);
	else
		UE_LOG(LogTemp, Warning, TEXT("Selectedd Wire Null in Vertical"))
}

void AWireSystem::MoveWireHorizontal(float Horizontal)
{
	float X = 0.0f;
	if (SelectedWire)
		X = SelectedWire->GetRelativeLocation().X;
	if (Horizontal < 0.000f)
		X = X-0.2f;
	else if(Horizontal > 0.000f)
		X = X+0.2f;

	X = FMath::Clamp(X, 6.0f, 25.0f);
	if(SelectedWire)
		SelectedWire->SetRelativeLocation(FVector(X, SelectedWire->GetRelativeLocation().Y, SelectedWire->GetRelativeLocation().Z), false, nullptr, ETeleportType::None);
	else
		UE_LOG(LogTemp, Warning,TEXT("Selectedd Wire Null in Horizontal"))
}

void AWireSystem::Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->IsInteracting = true;
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->InteractingObjectActor = this;
}

void AWireSystem::Away(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->IsInteracting = false;
	Cast<AHullsOfDeceptionCharacter>(OtherActor)->InteractingObjectActor = nullptr;


}

void AWireSystem::ClickReleased()
{
	if (SelectedWire) {
		if (SelectedWire->ComponentHasTag("Brown"))
		{
			//if (CanMoveBrown)
				SelectedWire->SetRelativeLocation(InnitialPosition);
		}
		else if (SelectedWire->ComponentHasTag("Green"))
		{
			//if (CanMoveGreen)
				SelectedWire->SetRelativeLocation(InnitialPosition);
		}
		else if (SelectedWire->ComponentHasTag("Blue"))
		{
			//if (CanMoveBlue)
				SelectedWire->SetRelativeLocation(InnitialPosition);
		}
		else if (SelectedWire->ComponentHasTag("Red"))
		{
			//if (CanMoveRed)
				SelectedWire->SetRelativeLocation(InnitialPosition);
		}
	}
	SelectedWire = nullptr;
}

void AWireSystem::OP()
{
	Cast <AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh()->SetVisibility(false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(this, 1.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	this->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	/// <summary>
	/// RegisterInput to Move Wire
	/// </summary>

	Input = FindComponentByClass<UInputComponent>();
	if (Input)
	{
		Input->BindAction("LeftMouseClick", IE_Pressed, this, &AWireSystem::DetectWire);
		Input->BindAction("LeftMouseClick", IE_Released, this, &AWireSystem::ClickReleased);
		Input->BindAxis("Turn", this, &AWireSystem::MoveWireHorizontal);
		Input->BindAxis("LookUp", this, &AWireSystem::MoveWireVertical);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Input is Null"));

}

void AWireSystem::TaskCompleted()
{
	Cast <AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh()->SetVisibility(true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 1.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	this->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	IsCompleted = true;
}


void AWireSystem::InitializeSomeThing()
{

	/// <summary>
	/// Collision Box Overlap
	/// </summary>
	CollisionBox = FindComponentByClass<UBoxComponent>();

	if (CollisionBox)
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWireSystem::Overlapped);
	else
		UE_LOG(LogTemp, Error, TEXT("CollisionBox Null"));

	if (CollisionBox)
		CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AWireSystem::Away);
	else
		UE_LOG(LogTemp, Error, TEXT("CollisionBox Null"));

	/// <summary>
	/// WireAttachment
	/// </summary>
	if (BrownAttachment)
	{
		BrownAttachment->OnComponentBeginOverlap.AddDynamic(this, &AWireSystem::AttachWire);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("BrownAttachmentNULL"));

	if (GreenAttachment)
	{
		GreenAttachment->OnComponentBeginOverlap.AddDynamic(this, &AWireSystem::AttachWire);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("GreenAttachmentNULL"));

	if (RedAttachment)
	{
		BlueAttachment->OnComponentBeginOverlap.AddDynamic(this, &AWireSystem::AttachWire);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("BlueAttachmentNULL"));

	if (BlueAttachment)
	{
		RedAttachment->OnComponentBeginOverlap.AddDynamic(this, &AWireSystem::AttachWire);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("RedAttachmentNULL"));

}
