// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/FindRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FNavLocation RandomPoint;
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	bool M;
	M = NavSystem->GetRandomPointInNavigableRadius(
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation(),
		1500.0f,
		RandomPoint,
		NULL,
		NULL);

	if (M)
	{
		OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector("TaskLocation", RandomPoint.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
