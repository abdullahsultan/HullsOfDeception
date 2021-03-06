// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskActorRefrences.h"
#include "GameFramework/Actor.h"
#include "HullsOfDeception/HullsOfDeceptionCharacter.h"
#include "TaskDivider.generated.h"

UCLASS()
class HULLSOFDECEPTION_API ATaskDivider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaskDivider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> TasksSprite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> ReactorTasksSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Tasks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> ReactorTasks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AHullsOfDeceptionCharacter*> Characters;

	UFUNCTION(BlueprintCallable)
	void DivideTasks();

	void Shuffle();

};
