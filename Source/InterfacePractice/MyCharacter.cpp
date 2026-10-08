// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include <Blueprint/UserWidget.h>
#include "HealthUIInterface.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 1. 위젯 생성 및 화면에 띄우기.
	if (HealthWidgetClass)
	{
		HealthWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HealthWidgetClass);
		if (HealthWidgetInstance)
		{
			HealthWidgetInstance->AddToViewport();

			// 시작할 때 풀피 상태로 초기화 전달.
			// Execute_함수명 형식으로 호출한다.
			IHealthUIInterface::Execute_UpdateHealth(HealthWidgetInstance, CurrentHealth, MaxHealth);
		}
	}
}

void AMyCharacter::ApplyDamageToSelf(float DamageAmount)
{
	// 체력 깎기(0 이하 안 떨어지게).
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);

	// 위젯이 인터페이스를 구현하고 있는 지 확인하고 호출.
	if (HealthWidgetInstance)
	{
		// 1. 체력바 갱신 신호 보내기.
		IHealthUIInterface::Execute_UpdateHealth(HealthWidgetInstance, CurrentHealth, MaxHealth);

		// 2. 체력이 30% 이하인지 판별해서 위험 경고 신호 보내기.
		const bool bIsLow = (CurrentHealth <= MaxHealth * 0.3f);
		IHealthUIInterface::Execute_OnLowHealthWarning(HealthWidgetInstance, bIsLow);
	}
	
}

