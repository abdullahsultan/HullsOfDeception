// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ReactorGame1.generated.h"

UCLASS()
class HULLSOFDECEPTION_API AReactorGame1 : public AActor, public IItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AReactorGame1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:


	UPROPERTY(BlueprintReadWrite, Category = "Lights and Switches")
		TArray<UStaticMeshComponent*> ArrayOfLights;

	UPROPERTY(BlueprintReadWrite, Category = "Lights and Switches")
		TArray<UStaticMeshComponent*> ArrayOfSwitches;

	UFUNCTION()
		void Overlapped(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void Away(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void OP();

	UFUNCTION(BlueprintCallable)
		void TaskCompleted();

	UInputComponent* Input = nullptr;

	UPROPERTY(BlueprintReadWrite)
		bool IsCompleted = false;

	UBoxComponent* BoxCollision = nullptr;

	void SetButtonOnOff();

	void SomeThingsToDo();

	TArray<int32> ButtonToPush;


};
