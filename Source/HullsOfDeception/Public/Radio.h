// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Radio.generated.h"



UCLASS()
class HULLSOFDECEPTION_API ARadio : public AActor, public IItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARadio();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	bool IsOverlapping;

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* LeftScreen;

	UBoxComponent* CollisionBox = nullptr;

	UFUNCTION()
		void Overlapped(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void Away(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) ;

	UFUNCTION(BlueprintCallable)
		void OP();

	UFUNCTION(BlueprintCallable)
		void TaskCompleted();

	UPROPERTY(BlueprintReadWrite)
	bool IsCompleted = false;
};
