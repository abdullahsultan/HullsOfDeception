// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CheckInteractionService.generated.h"

/**
 * 
 */
UCLASS()
class HULLSOFDECEPTION_API UCheckInteractionService : public UBTService
{
	GENERATED_BODY()
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
