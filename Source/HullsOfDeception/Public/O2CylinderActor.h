 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Item.h"
#include "O2CylinderActor.generated.h"

UCLASS()
class HULLSOFDECEPTION_API AO2CylinderActor : public AActor, public IItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AO2CylinderActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadWrite)
		float O2 = 0.0f;

	UPROPERTY(BlueprintReadWrite)
		UBoxComponent* BoxCollision = nullptr;

	UPROPERTY(BlueprintReadWrite)
		bool IsCompleted = false;

	void IncrementO2();
	void DecrementO2();

	UFUNCTION()
		void Interact(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void Leave(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
