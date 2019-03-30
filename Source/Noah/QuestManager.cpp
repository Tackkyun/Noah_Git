// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "QuestManager.h"
#include "StringParser.h"

// Sets default values
AQuestManager::AQuestManager() : ClearRange(0), ClearPosition(0, 0, 0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuestManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AQuestManager::AddHuman(FString humanName, AHuman* human)
{
	if (human != nullptr) {
		m_humanMap.insert(pair<FString, AHuman*>(humanName, human));
		return true;
	}

	return false;
}

void AQuestManager::FindRange(FString clearDemand)
{
	//문자열에서 거리와 범위를 얻어와준다.
	StringParser::TableRangeParser(clearDemand, ClearPosition, ClearRange);
}

bool AQuestManager::RangeCheck(FVector targetPosition)
{
	//범위 내에 들어왔는지 검사해준다.
	FVector v = targetPosition - ClearPosition;
	float length = v.Size();
	if (length < ClearRange) {
		return true;
	}
	return false;
}