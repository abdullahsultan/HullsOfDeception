// Fill out your copyright notice in the Description page of Project Settings.


#include "ReactorGameNo2Widget.h"

#include <string>

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UReactorGameNo2Widget::NativeConstruct()
{
	Super::NativeConstruct();
	WidgetHandle.SetNum(10, true);
	DoSomething();
}


void UReactorGameNo2Widget::DoSomething()
{

	WidgetHandle[0].Button = Btn0;
	WidgetHandle[0].Text = Text0;

	WidgetHandle[1].Button = Btn1;
	WidgetHandle[1].Text = Text1;

	WidgetHandle[2].Button = Btn2;
	WidgetHandle[2].Text = Text2;

	WidgetHandle[3].Button = Btn3;
	WidgetHandle[3].Text = Text3;

	WidgetHandle[4].Button = Btn4;
	WidgetHandle[4].Text = Text4;

	WidgetHandle[5].Button = Btn5;
	WidgetHandle[5].Text = Text5;

	WidgetHandle[6].Button = Btn6;
	WidgetHandle[6].Text = Text6;

	WidgetHandle[7].Button = Btn7;
	WidgetHandle[7].Text = Text7;

	WidgetHandle[8].Button = Btn8;
	WidgetHandle[8].Text = Text8;

	WidgetHandle[9].Button = Btn9;
	WidgetHandle[9].Text = Text9;

		int acc = 0;
	for (int x=0; x<100; x++)
	{
		int32 T = FMath::RandRange(1, 10);
		FString Fst = FString::FromInt(T);
		if(!Contains(T))
		{
            if (acc >=10){break;}
     		WidgetHandle[acc].Value	= T;
			WidgetHandle[acc].Text->SetText(FText::AsCultureInvariant(Fst));
			acc++;
		}
	}

	

	for (int x = 0; x < 10; x++)
	{
		if (WidgetHandle[x].Button == Btn0)
		{
			ButtonDisabled.Broadcast(Btn0);
			Btn0->OnClicked.AddDynamic(this, &UReactorGameNo2Widget::Clicked);
		}
		//WidgetHandle[x].Button->OnClicked.AddDynamic(this, &UReactorGameNo2Widget::Clicked);
	}
}


bool UReactorGameNo2Widget::Contains(int val)
{
	for (int x = 0; x < 10; x++)
	{
		if (WidgetHandle[x].Value == val)
			return true;
	}
	return false;
}

void UReactorGameNo2Widget::Clicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked"));
	if(WidgetHandle[0].Button==Btn0)
	{
		Btn0->SetIsEnabled(false);
	}
	//ButtonDisabled.AddDynamic(this, &UReactorGameNo2Widget::DisableClickedButton);
	//FHitResult Hit;
	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_MAX, true, Hit);
	//DisableClickedButton(Hit.GetComponent()->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("Component %s"), *Hit.GetComponent()->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("Component %s"), *Hit.GetActor()->GetName());
}

void UReactorGameNo2Widget::DisableClickedButton(UButton* B)
{
	UE_LOG(LogTemp, Warning, TEXT("Disabled"));
	B->SetIsEnabled(false);
}
