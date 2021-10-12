// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/RandomPatrol.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type URandomPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FVector Loc = OwnerComp.GetBlackboardComponent()->GetValueAsVector("TaskLocation");
	OwnerComp.GetAIOwner()->MoveToLocation(Loc, 0.0f, false, true, false, false, nullptr, false);
	return EBTNodeResult::Succeeded;
}
