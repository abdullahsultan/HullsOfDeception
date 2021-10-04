// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskDivider.h"

// Sets default values
ATaskDivider::ATaskDivider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATaskDivider::BeginPlay()
{
	Super::BeginPlay();
	DivideTasks();
	
}

// Called every frame
void ATaskDivider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATaskDivider::DivideTasks()
{
	int Ch = 0;
	while (Ch < 5)
	{
		int32 Rand = FMath::RandRange(0, Tasks.Num());
		if(Rand <= 11 && Rand < Tasks.Num())
		{
			Characters[Ch]->Tasks.Add(Tasks[Rand]);
			Tasks.Remove(Tasks[Rand]);
			Ch++;
		}
		else if(Rand == 12 || Rand == 13)
		{
			Characters[Ch]->Tasks.Add(Tasks[12]);
			Characters[Ch]->Tasks.Add(Tasks[13]);
			Tasks.Remove(Tasks[12]);
			Tasks.Remove(Tasks[13]);
			Ch++;
		}
		else if (Rand == 14 || Rand == 15)
		{
			Characters[Ch]->Tasks.Add(Tasks[14]);
			Characters[Ch]->Tasks.Add(Tasks[15]);
			Tasks.Remove(Tasks[14]);
			Tasks.Remove(Tasks[15]);
			Ch++;
		}

	}
}

