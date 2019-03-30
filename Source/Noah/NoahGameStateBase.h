// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "NoahGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class NOAH_API ANoahGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	ANoahGameStateBase();

	UPROPERTY(BlueprintReadWrite, Category = "GameState")
		int32 RainValue;
	UPROPERTY(BlueprintReadWrite, Category = "GameState")
		int Day;
	
public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "GameState")
		void AddDay();
};
