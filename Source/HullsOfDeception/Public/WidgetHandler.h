// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class HULLSOFDECEPTION_API WidgetHandler
{
public:
	WidgetHandler();
	~WidgetHandler();

	class UButton* Button;
	class UTextBlock* Text;
	int32 Value = -1;
};
