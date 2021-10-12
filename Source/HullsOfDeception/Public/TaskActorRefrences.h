// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskActorRefrences.generated.h"

/**
 * 
 */
UCLASS()
class HULLSOFDECEPTION_API UTaskActorRefrences : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* TargetPoint;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* TaskActor;
};
