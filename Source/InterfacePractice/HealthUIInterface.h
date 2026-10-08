// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthUIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UHealthUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INTERFACEPRACTICE_API IHealthUIInterface
{
	GENERATED_BODY()

public:
	// 체력이 변경될 때마다 UI에 알려주는 함수.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health UI")
	void UpdateHealth(float CurrentHealth, float MaxHealth);

	// 체력이 30% 이하로 떨어지거나 회복되었을 때 경고 상태를 알리는 함수.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health UI")
	void OnLowHealthWarning(bool bIsLowHealth);
};
