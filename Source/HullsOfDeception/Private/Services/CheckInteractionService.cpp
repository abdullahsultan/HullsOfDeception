// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/CheckInteractionService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HullsOfDeception/HullsOfDeceptionCharacter.h"


void UCheckInteractionService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AHullsOfDeceptionCharacter *Ch= Cast<AHullsOfDeceptionCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsReached", Ch->IsInteracting);
}
