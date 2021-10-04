// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CardSwipe.generated.h"

UCLASS()
class HULLSOFDECEPTION_API ACardSwipe : public AActor, public IItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardSwipe();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UInputComponent* Input = nullptr;

	bool CanMoveCard = false;

	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* CardMesh = nullptr;

	UBoxComponent* CollisionBox = nullptr;

	UFUNCTION()
		void Overlapped(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void Away(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void OP();

	UFUNCTION(BlueprintCallable)
		void TaskCompleted();

	void SetCard();
	void ResetCard();
	void MoveCard(float X);

	FTimerHandle TimeHandler;
	float Sec = 0.0f;
	UFUNCTION()
		void SecondCount();

	UPROPERTY(BlueprintReadWrite)
	bool IsCompleted = false;

	UFUNCTION(BlueprintCallable)
		void AutoCompleteForAI();

	void CheckWin();

};
