// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Inventory.h"
#include "NPC.generated.h"

UENUM(BlueprintType)
enum class ENPCStateEnum : uint8
{
	VE_Idle		UMETA(DisplayName = "Idle"),
	VE_Trace	UMETA(DisplayName = "Trace"),
	VE_Attack	UMETA(DisplayName = "Attack"),
	VE_Run		UMETA(DisplayName = "Run"),
	VE_RunAway	UMETA(DisplayName = "RunAway"),
	VE_Dead		UMETA(DisplayName = "Dead")
};

UCLASS()
class NOAH_API ANPC : public ACharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NPC")
		TArray<ENPCStateEnum> NPCStateList;
	UPROPERTY(BlueprintReadWrite, Category = "NPC")
		ENPCStateEnum CurrentNPCState;
	UPROPERTY(BlueprintReadWrite, Category = "NPC")
		float Health;
	UPROPERTY(BlueprintReadWrite, Category = "NPC")
		UInventory* Inventory;
	UPROPERTY(BlueprintReadWrite, Category = "NPC")
		bool bLookTarget;
	UPROPERTY(BlueprintReadWrite, Category = "NPC")
		float traceRange;
public:
	// Sets default values for this character's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "NPC")
		bool FindStateList(ENPCStateEnum state);
	UFUNCTION(BlueprintCallable, Category = "NPC")
		ENPCStateEnum NPCStateUpdate(APawn* target);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "NPC")
		void Damaged(float damage);
	//시선 앞에 타겟이 보이는지 검사
	UFUNCTION(BlueprintCallable, Category = "NPC")
		bool LookTarget(FVector targetLocation, float angle, float distance);
};
