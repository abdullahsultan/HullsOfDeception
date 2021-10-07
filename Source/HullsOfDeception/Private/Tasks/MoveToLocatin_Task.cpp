// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/MoveToLocatin_Task.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UMoveToLocatin_Task::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	FVector Loc = OwnerComp.GetBlackboardComponent()->GetValueAsVector("TaskLocation");
	OwnerComp.GetAIOwner()->MoveToLocation(Loc, 50.0f, false, true, false, false, nullptr, false);

	return EBTNodeResult::Succeeded;
}
