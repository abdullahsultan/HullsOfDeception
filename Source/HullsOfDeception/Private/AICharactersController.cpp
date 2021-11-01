// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharactersController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "HullsOfDeception/HullsOfDeceptionCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DeathInterface.h"



void AAICharactersController::BeginPlay()
{
	Super::BeginPlay();

	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsBool("ShouldKill", false);
		GetBlackboardComponent()->SetValueAsBool("IsReached", false);
		GetBlackboardComponent()->SetValueAsBool("TasksCompleted", false);
		GetBlackboardComponent()->SetValueAsVector("TaskLocation", Cast<AHullsOfDeceptionCharacter>(GetPawn())->Tasks[0]->GetActorLocation());
		GetBlackboardComponent()->SetValueAsInt("TaskNo", 0);
	}

	//Sense_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sense_Sight"));

	/*Sense_Sight->SightRadius = 3000;
	Sense_Sight->LoseSightRadius = 3500;
	Sense_Sight->PeripheralVisionAngleDegrees = 180;
	Sense_Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sense_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sense_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sense_Sight->AutoSuccessRangeFromLastSeenLocation = 1500;*/

	/*AIPerceptionComponent->bAutoActivate = true;

	AIPerceptionComponent->ConfigureSense(*Sense_Sight);*/
	/*AIPerceptionComponent = FindComponentByClass<UAIPerceptionComponent>();
	if(Cast<AHullsOfDeceptionCharacter>(GetPawn())->IsImposter)
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AAICharactersController::OnPlayerDetectedforImposter);*/
	AIPerceptionComponent = FindComponentByClass<UAIPerceptionComponent>();
}

void AAICharactersController::OnPlayerDetectedforImposter()
{
	TArray<AActor*> DetectedPawn;
	AIPerceptionComponent->GetPerceivedActors(Sense_Sight, DetectedPawn);
	
	UE_LOG(LogTemp, Warning, TEXT("NNUM %d" ), DetectedPawn.Num());
	if (DetectedPawn.Num() == 1)
	{
		//UE_LOG(LogTemp, Warning, TEXT("NNUM %d : Name %s"), DetectedPawn.Num(), *DetectedPawn[0]->GetName());
		if(!Cast<AHullsOfDeceptionCharacter>(DetectedPawn[0])->IsImposter)
		{
				GetBlackboardComponent()->SetValueAsBool("ShouldKill", true);
				Ch = DetectedPawn[0];
				GetBlackboardComponent()->SetValueAsVector("CharacterLocation",DetectedPawn[0]->GetActorLocation());
				GetBlackboardComponent()->SetValueAsObject("Character", DetectedPawn[0]);
		}
		else
		{
			GetBlackboardComponent()->SetValueAsBool("ShouldKill", false);
			GetBlackboardComponent()->SetValueAsObject("Character", nullptr);
		}
	}
	else
	{
		GetBlackboardComponent()->SetValueAsBool("ShouldKill", false);
		GetBlackboardComponent()->SetValueAsObject("Character", nullptr);
	}
}

void AAICharactersController::OnPlayerDetectedforNonImposter()
{
	TArray<AActor*> DetectedPawn;
	AIPerceptionComponent->GetPerceivedActors(Sense_Sight, DetectedPawn);
	for (int X=0; X<DetectedPawn.Num(); X++)
	{
		if (Cast<AHullsOfDeceptionCharacter>(DetectedPawn[X])->IsDead)
		{
			IDeathInterface::Execute_FoundDead(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
				//FoundDead(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			break;
		}
	}
}

void AAICharactersController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Cast<AHullsOfDeceptionCharacter>(GetPawn())->IsImposter)
	{
		OnPlayerDetectedforImposter();
	}
	else
	{
		OnPlayerDetectedforNonImposter();
	}
	
}

