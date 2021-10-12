// Fill out your copyright notice in the Description page of Project Settings.


#include "ImposterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HullsOfDeception/HullsOfDeceptionCharacter.h"
#include "Perception/AIPerceptionComponent.h"

void AImposterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsBool("IsReached", false);
		GetBlackboardComponent()->SetValueAsBool("ShouldKill", false);
		GetBlackboardComponent()->SetValueAsBool("TasksCompleted", false);
		GetBlackboardComponent()->SetValueAsVector("TaskLocation", Cast<AHullsOfDeceptionCharacter>(GetPawn())->Tasks[0]->GetActorLocation());
		GetBlackboardComponent()->SetValueAsInt("TaskNo", 0);
	}

	Sense_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sense_Sight"));
	
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerceptionComponent"));
	Sense_Sight->SightRadius = 3000;
	Sense_Sight->LoseSightRadius = 3500;
	Sense_Sight->PeripheralVisionAngleDegrees = 180;
	Sense_Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sense_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sense_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sense_Sight->AutoSuccessRangeFromLastSeenLocation = 1500;

	AIPerceptionComponent->bAutoActivate = true;

	AIPerceptionComponent->ConfigureSense(*Sense_Sight);
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AImposterAIController::OnPlayerDetected);
}

void AImposterAIController::OnPlayerDetected(const TArray<AActor*>& DetectedPawn)
{
	if(DetectedPawn.Num() == 1)
	{
		GetBlackboardComponent()->SetValueAsBool("ShouldKill", true);
		FVector ChaseLoc = DetectedPawn[0]->GetActorLocation();
		GetBlackboardComponent()->SetValueAsVector("TaskLocation", ChaseLoc);		
	}
}
