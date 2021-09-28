// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetHandler.h"
#include "Blueprint/UserWidget.h"
#include "ReactorGameNo2Widget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickDisable, UButton*, B);

UCLASS()
class HULLSOFDECEPTION_API UReactorGameNo2Widget : public UUserWidget
{
	GENERATED_BODY()

	void NativeConstruct() override;

	UPROPERTY(BlueprintAssignable)
	FOnClickDisable ButtonDisabled;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UButton* Btn0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UButton* Btn1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UButton* Btn2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UButton* Btn3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UButton* Btn4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UButton* Btn5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UButton* Btn6;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UButton* Btn7;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UButton* Btn8;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UButton* Btn9;

	
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text0;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text1;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text2;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text3;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text4;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text5;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text6;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text7;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text8;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text9;

	bool Contains(int val);
	void DoSomething();

	TArray<WidgetHandler> WidgetHandle;

	UFUNCTION()
		void Clicked();

	UFUNCTION()
	void DisableClickedButton(UButton* B);

	int32 NoOfButtonClicked = 0;

};
