// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathInterface.h"
#include "VotingSystemActor.generated.h"

UCLASS()
class HULLSOFDECEPTION_API AVotingSystemActor : public AActor, public IDeathInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVotingSystemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
