// Fill out your copyright notice in the Description page of Project Settings.


#include "ReactorGameNo2Widget.h"

#include <string>

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

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

	Btn0->OnClicked.AddDynamic(this, &UReactorGameNo2Widget::Clicked0);
	Btn1->OnClicked.AddDynamic(this, &UReactorGameNo2Widget::Clicked1);
	Btn2->OnClicked.AddDynamic(this, &UReactorGameNo2Widget::Clicked2);
	Btn3->OnClicked.AddDynamic(this, &UReactorGameNo2Widget::Clicked3);
	Btn4->OnClicked.AddDynamic(this, &UReactorGameNo2Widget::Clicked4);
	Btn5->OnClicked.AddDynamic(this, &UReactorGameNo2Widget::Clicked5);
	Btn6->OnClicked.AddDynamic(this, &UReactorGameNo2Widget::Clicked6);
	Btn7->OnClicked.AddDynamic(this, &UReactorGameNo2Widget::Clicked7);
	Btn8->OnClicked.AddDynamic(this, &UReactorGameNo2Widget::Clicked8);
	Btn9->OnClicked.AddDynamic(this, &UReactorGameNo2Widget::Clicked9);

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

void UReactorGameNo2Widget::Clicked0()
{
	Btn0->SetIsEnabled(false);
	Check(WidgetHandle[0].Value);
}

void UReactorGameNo2Widget::Clicked1()
{
	Btn1->SetIsEnabled(false);
	Check(WidgetHandle[1].Value);
}

void UReactorGameNo2Widget::Clicked2()
{
	Btn2->SetIsEnabled(false);
	Check(WidgetHandle[2].Value);
}

void UReactorGameNo2Widget::Clicked3()
{
	Btn3->SetIsEnabled(false);
	Check(WidgetHandle[3].Value);
}

void UReactorGameNo2Widget::Clicked4()
{
	Btn4->SetIsEnabled(false);
	Check(WidgetHandle[4].Value);
}

void UReactorGameNo2Widget::Clicked5()
{
	Btn5->SetIsEnabled(false);
	Check(WidgetHandle[5].Value);
}

void UReactorGameNo2Widget::Clicked6()
{
	Btn6->SetIsEnabled(false);
	Check(WidgetHandle[6].Value);
}

void UReactorGameNo2Widget::Clicked7()
{
	Btn7->SetIsEnabled(false);
	Check(WidgetHandle[7].Value);
}

void UReactorGameNo2Widget::Clicked8()
{
	Btn8->SetIsEnabled(false);
	Check(WidgetHandle[8].Value);
}

void UReactorGameNo2Widget::Clicked9()
{
	Btn9->SetIsEnabled(false);
	Check(WidgetHandle[9].Value);
}

void UReactorGameNo2Widget::Check(int32 ButtonNo)
{
	if (Counter + 1 != ButtonNo)
		ResetButtons();
	else if (Counter + 1 == ButtonNo && ButtonNo == 10)
	{
		Completed();
	}
	else
		Counter = ButtonNo;

}

void UReactorGameNo2Widget::ResetButtons()
{
	for (auto ErrorHist : WidgetHandle)
	{
		ErrorHist.Button->SetIsEnabled(true);
	}
	Counter = 0;
}

void UReactorGameNo2Widget::Completed()
{
	IItem::Execute_Won(this);
	RemoveFromParent();
}


