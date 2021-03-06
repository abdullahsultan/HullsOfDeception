// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/UpdateTask_Task.h"
#include "HullsOfDeception/HullsOfDeceptionCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UUpdateTask_Task::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AHullsOfDeceptionCharacter* Ch= Cast<AHullsOfDeceptionCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	OwnerComp.GetBlackboardComponent()->SetValueAsInt("TaskNo", OwnerComp.GetBlackboardComponent()->GetValueAsInt("TaskNo") + 1);
	if (OwnerComp.GetBlackboardComponent()->GetValueAsInt("TaskNo") < Ch->Tasks.Num())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("TaskLocation", Ch->Tasks[OwnerComp.GetBlackboardComponent()->GetValueAsInt("TaskNo")]->GetActorLocation());
	}
	else
	{
		OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool("TasksCompleted", true);

		if(Cast<AHullsOfDeceptionCharacter>(OwnerComp.GetAIOwner()->GetPawn())->IsImposter)
			IDeathInterface::Execute_EnableSabotage(OwnerComp.GetAIOwner());
	}
	Ch->IsInteracting = false;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsReached", false);
	return EBTNodeResult::Succeeded;
}
