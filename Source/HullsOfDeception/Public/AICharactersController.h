// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AICharactersController.generated.h"

/**
 * 
 */
UCLASS()
class HULLSOFDECEPTION_API AAICharactersController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UAIPerceptionComponent* AIPerceptionComponent;

	TSubclassOf<UAISense_Sight> Sense_Sight;

	UFUNCTION()
		void OnPlayerDetectedforImposter();

	UFUNCTION()
		void OnPlayerDetectedforNonImposter(const TArray<AActor*>& DetectedPawn);

	UPROPERTY(BlueprintReadWrite)
	AActor* Ch = nullptr;

	void Tick(float DeltaTime) override;

};
