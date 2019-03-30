// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include <map>
#include "QuestManager.generated.h"

using namespace std;

UCLASS()
class NOAH_API AQuestManager : public AActor
{
	GENERATED_BODY()
private:
	map<FString, AHuman*> m_humanMap;
public:
	UPROPERTY(BlueprintReadWrite, Category = "QuestManager")
		TArray<FString> CurrentQuest;
	UPROPERTY(BlueprintReadWrite, Category = "QuestManager")
		FVector ClearPosition;
	UPROPERTY(BlueprintReadWrite, Category = "QuestManager")
		int32 ClearRange;

public:
	// Sets default values for this actor's properties
	AQuestManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		bool AddHuman(FString humanName, AHuman* human);
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		void FindRange(FString clearDemand);
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		bool RangeCheck(FVector targetPosition);
};
