// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DeathInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDeathInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HULLSOFDECEPTION_API IDeathInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Die();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Kill();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void FoundDead();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void EnableSabotage();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void RepairSabotage(FVector SabotageLocation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void AISabotage();
};
