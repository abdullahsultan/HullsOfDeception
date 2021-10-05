// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Item.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HULLSOFDECEPTION_API IItem
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void StartOperation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void TooFast();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void TooSlow();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Won();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void AtEnd();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SpriteEnableDisable();
};
