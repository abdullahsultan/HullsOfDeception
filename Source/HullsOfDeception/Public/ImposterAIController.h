// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "ImposterAIController.generated.h"

/**
 * 
 */
UCLASS()
class HULLSOFDECEPTION_API AImposterAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAIPerceptionComponent* AIPerceptionComponent;

	UAISenseConfig_Sight* Sense_Sight;

	UFUNCTION()
		void OnPlayerDetected(const TArray<AActor*>& DetectedPawn);
	
};
