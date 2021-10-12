// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/CheckInteractionService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HullsOfDeception/HullsOfDeceptionCharacter.h"


void UCheckInteractionService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	FVector V = OwnerComp.GetAIOwner()->GetCharacter()->GetActorLocation();
	FVector T = OwnerComp.GetBlackboardComponent()->GetValueAsVector("TaskLocation");
	FVector Delta(10.0f, 10.0f, 10.0f);
	if(V==T)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsReached", true);
	}
	else
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsReached", false);
	

	//AHullsOfDeceptionCharacter *Ch= Cast<AHullsOfDeceptionCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	//if(Ch)
	//{
	//UE_LOG(LogTemp, Warning, TEXT("Name: %s  Status: %d"), *Ch->GetName(), Ch->IsInteracting);
	//if(OwnerComp.GetBlackboardComponent())
	//OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsReached", Ch->IsInteracting);
	//}
	//else
	//	UE_LOG(LogTemp, Warning, TEXT("CH is null"));
}
