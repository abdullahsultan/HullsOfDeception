// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharactersController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "HullsOfDeception/HullsOfDeceptionCharacter.h"

void AAICharactersController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAICharactersController::InitFirstTask()
{
	GetBlackboardComponent()->SetValueAsBool("IsReached", false);
	GetBlackboardComponent()->SetValueAsBool("TasksCompleted", false);
	GetBlackboardComponent()->SetValueAsVector("TaskLocation", Cast<AHullsOfDeceptionCharacter>(GetPawn())->Tasks[0]->GetActorLocation());
	GetBlackboardComponent()->SetValueAsInt("TaskNo", 0);
}


