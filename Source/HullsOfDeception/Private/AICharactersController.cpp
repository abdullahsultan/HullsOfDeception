// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharactersController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "HullsOfDeception/HullsOfDeceptionCharacter.h"
#include "Perception/AIPerceptionComponent.h"

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
	AIPerceptionComponent = FindComponentByClass<UAIPerceptionComponent>();
	if(Cast<AHullsOfDeceptionCharacter>(GetPawn())->IsImposter)
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AAICharactersController::OnPlayerDetectedforImposter);

	else
		AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AAICharactersController::OnPlayerDetectedforNonImposter);

}

void AAICharactersController::OnPlayerDetectedforImposter(const TArray<AActor*>& DetectedPawn)
{

	for(int x= 0 ; x< DetectedPawn.Num(); x++)
		UE_LOG(LogTemp, Warning, TEXT("Name: %s Detected"), *DetectedPawn[x]->GetName());
	UE_LOG(LogTemp, Warning, TEXT("NNUM %d "), DetectedPawn.Num());
	if (DetectedPawn.Num() == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inside If No of Pwns: %d "), DetectedPawn.Num());
		if(!Cast<AHullsOfDeceptionCharacter>(DetectedPawn[0])->IsImposter)
		{
			Ch = DetectedPawn[0];
			GetBlackboardComponent()->SetValueAsBool("ShouldKill", true);
			GetBlackboardComponent()->SetValueAsVector("CharacterLocation",DetectedPawn[0]->GetActorLocation());
			GetBlackboardComponent()->SetValueAsObject("Character", DetectedPawn[0]);
		}
	}
	else
	{
		GetBlackboardComponent()->SetValueAsBool("ShouldKill", false);
		GetBlackboardComponent()->SetValueAsObject("Character", nullptr);
	}
}

void AAICharactersController::OnPlayerDetectedforNonImposter(const TArray<AActor*>& DetectedPawn)
{
}


