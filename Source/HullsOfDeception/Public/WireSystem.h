// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "WireSystem.generated.h"

UCLASS()
class HULLSOFDECEPTION_API AWireSystem : public AActor,public IItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWireSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UBoxComponent* CollisionBox = nullptr;

	////////////////////////////////////////////////////Wires//////////////////////////////////////////////
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* BrownWire = nullptr;

	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* GreenWire = nullptr;

	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* RedWire = nullptr;

	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* BlueWire = nullptr;

	////////////////////////////////////////////////////Wires Attachment//////////////////////////////////////////////
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* BrownAttachment = nullptr;

	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* GreenAttachment = nullptr;

	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* BlueAttachment = nullptr;

	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* RedAttachment = nullptr;

	//bool CanMoveBrown = true;
	//bool CanMoveGreen = true;
	//bool CanMoveRed = true;
	//bool CanMoveBlue = true;

	int32 NoOfWires = 0;

	FVector InnitialPosition;



	UStaticMeshComponent* SelectedWire;

	UInputComponent* Input = nullptr;

	void DetectWire();
	void ClickReleased();

	UFUNCTION(BlueprintCallable)
	void MoveWireVertical(float Vertical);
	UFUNCTION(BlueprintCallable)
	void MoveWireHorizontal(float Horizontal);

	void InitializeSomeThing();

	UFUNCTION()
		void AttachWire(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void Overlapped(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void Away(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void OP();

	UFUNCTION(BlueprintCallable)
		void TaskCompleted();

	UPROPERTY(BlueprintReadWrite)
		bool IsCompleted = false;

};
