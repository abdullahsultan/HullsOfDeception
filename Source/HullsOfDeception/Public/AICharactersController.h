// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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

	UFUNCTION(BlueprintCallable)
		void InitFirstTask();
};
