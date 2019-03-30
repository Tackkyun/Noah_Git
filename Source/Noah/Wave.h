// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Wave.generated.h"

UCLASS()
class NOAH_API AWave : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AWave();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Wave")
		void UpWave(int RainValue);
};
