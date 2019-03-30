// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "NPC.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

// Sets default values
ANPC::ANPC() : Health(10.f), Inventory(nullptr), bLookTarget(false), traceRange(1500)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ANPC::FindStateList(ENPCStateEnum state)
{
	if (NPCStateList.Find(state) != -1) {
		return true;
	}
	return false;
}

ENPCStateEnum ANPC::NPCStateUpdate(APawn* target)
{
	if (target == nullptr) {
		return ENPCStateEnum::VE_Idle;
	}

	float distance = FVector::Dist(target->GetActorLocation(), this->GetActorLocation());
	
	if (Health <= 0) {
		return ENPCStateEnum::VE_Dead;
	}

	if (NPCStateList.Find(ENPCStateEnum::VE_RunAway) != -1) {
		if (Health <= 7) {
			return ENPCStateEnum::VE_RunAway;
		}
	}

	if (NPCStateList.Find(ENPCStateEnum::VE_Attack) != -1) {
		if (distance <= 200) {
			return ENPCStateEnum::VE_Attack;
		}
	}

	if (NPCStateList.Find(ENPCStateEnum::VE_Trace) != -1) {
		if (distance <= traceRange) {
			return ENPCStateEnum::VE_Trace;
		}
	}
	
	

	return ENPCStateEnum::VE_Idle;
}

bool ANPC::LookTarget(FVector targetLocation, float angle, float distance)
{

	//타겟이 시야에 들어와있는지 검사하기 위한 내적.
	FVector  targetVector = targetLocation - GetActorLocation();
	targetVector.Normalize();
	float dotValue = UKismetMathLibrary::Dot_VectorVector(targetVector, GetActorForwardVector());
	//타겟과의 거리구하기
	float targetDist = FVector::Distance(targetLocation, GetActorLocation());

	//타겟과의 범위와 거리 안에 있다면 true를 반환한다.
	if (dotValue >= angle) {
		if (targetDist <= distance) {
			bLookTarget = true;
			return true;
		}
	}
	else {
		bLookTarget = false;
		return false;
	}
	bLookTarget = false;
	return false;
}