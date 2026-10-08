// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class INTERFACEPRACTICE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// 체력 관련 변수들.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float CurrentHealth = 100.f;

	// 화면에 띄울 위젯 클래스(블루프린트에서 고를 수 있게).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> HealthWidgetClass;

	// 실제로 생성된 위젯 객체(특정 위젯 타입 대신 일반 UUserWidget*으로 보관).
	UPROPERTY()
	TObjectPtr<class UUserWidget> HealthWidgetInstance;

public:
	// 데미지를 입히는 테스트 함수(키보드 1번이나 데미지 이벤트에서 호출).
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ApplyDamageToSelf(float DamageAmount);

};
