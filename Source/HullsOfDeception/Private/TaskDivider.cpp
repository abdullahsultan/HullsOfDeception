// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskDivider.h"

#include "Kismet/GameplayStatics.h"

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
}

// Called every frame
void ATaskDivider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATaskDivider::DivideTasks()
{
	Shuffle();
	/// <summary>
	/// Ragular Tasks
	/// </summary>
	int32 Ch = 0;
	for (int32 Task=0; Task<12; Task = Task+2)
	{
		if (Ch < 5)
		{
			Characters[Ch]->Tasks.Add(Tasks[Task]);
			Characters[Ch]->Tasks.Add(Tasks[Task+1]);
			Characters[Ch]->TasksSprite.Add(TasksSprite[Task]);
			Characters[Ch]->TasksSprite.Add(TasksSprite[Task + 1]);

			Ch++;
		}
		else if(Ch == 5)
		{
			Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Tasks.Add(Tasks[Task]);
			Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Tasks.Add(Tasks[Task+1]);
			Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->TasksSprite.Add(TasksSprite[Task]);
			Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->TasksSprite.Add(TasksSprite[Task + 1]);
		}
	}

	/// <summary>
	/// RactorTasks
	/// </summary>
	int32 Rand = FMath::RandRange(0, 2);
	Characters[Rand]->Tasks.Add(ReactorTasks[0]);
	Characters[Rand]->Tasks.Add(ReactorTasks[1]);
	Characters[Rand]->TasksSprite.Add(ReactorTasksSprite[0]);
	Characters[Rand]->TasksSprite.Add(ReactorTasksSprite[1]);

	Rand = FMath::RandRange(3, 5);
	if (Rand != 5)
	{
		Characters[Rand]->Tasks.Add(ReactorTasks[2]);
		Characters[Rand]->Tasks.Add(ReactorTasks[3]);
		Characters[Rand]->TasksSprite.Add(ReactorTasksSprite[2]);
		Characters[Rand]->TasksSprite.Add(ReactorTasksSprite[3]);
	}
	else
	{
		Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Tasks.Add(ReactorTasks[2]);
		Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Tasks.Add(ReactorTasks[3]);
		Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->TasksSprite.Add(ReactorTasksSprite[2]);
		Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->TasksSprite.Add(ReactorTasksSprite[3]);
	}


	/////////////////////////////////////////////Choosing Imposters/////////////////////////////////////////////
	Rand = FMath::RandRange(0, 2);
	Characters[Rand]->IsImposter = true;

	/*Rand = FMath::RandRange(3, 5);
	if (Rand != 5)
	{
		Characters[Rand]->IsImposter = true;
	}
	else
	{
		Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->IsImposter = true;;
	}*/
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void ATaskDivider::Shuffle()
{
	for(int X=0; X<Tasks.Num(); X++)
	{
		int Rand = FMath::RandRange(0, Tasks.Num()-1);
		Tasks.Swap(X, Rand);
		TasksSprite.Swap(X, Rand);

	}
}


//Ints.SetNum(6);
	//for (int X=0; X<6; )
	//{
	//	int32 Rand = FMath::RandRange(0, 5);
	//	if(!Ints.Contains(Rand))
	//	{
	//		Ints.Add(Rand);
	//		X++;
	//	}
	//}

	//int Ch = 0;
	//for (int Task = 0; Task < 15; )
	//{
	//	if(Task == 0 || Task == 14)
	//	{
	//		if(Task == 0)
	//		{
	//			if(Ints[Ch] != 5)
	//			{
	//				Characters[Ints[Ch]]->Tasks.Add(Tasks[0]);
	//				Characters[Ints[Ch]]->Tasks.Add(Tasks[1]);
	//				Task += 2;
	//			}
	//			else
	//			{
	//				Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Tasks.Add(Tasks[0]);
	//				Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Tasks.Add(Tasks[1]);
	//				Task += 2;
	//			}
	//		}
	//		else if(Task == 14)
	//		{
	//			if (Ints[Ch] != 5)
	//			{
	//				Characters[Ints[Ch]]->Tasks.Add(Tasks[14]);
	//				Characters[Ints[Ch]]->Tasks.Add(Tasks[15]);
	//				Task += 2;
	//			}
	//			else
	//			{
	//				Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Tasks.Add(Tasks[14]);
	//				Cast<AHullsOfDeceptionCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Tasks.Add(Tasks[15]);
	//				Task += 2;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		if(Ints[Ch] != 5)
	//		{
	//			Characters[Ints[Ch]]->Tasks.Add(Tasks[Task]);
	//			
	//		}
	//	}
	//}