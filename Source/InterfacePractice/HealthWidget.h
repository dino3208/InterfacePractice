// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthUIInterface.h"
#include "HealthWidget.generated.h"


// 전방 선언.
class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class INTERFACEPRACTICE_API UHealthWidget : 
	public UUserWidget,
	public IHealthUIinterface
{
	GENERATED_BODY()
	
public: 

};
