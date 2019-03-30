// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Inventory.h"
#include "MapObject.generated.h"

//Delegate ¸ÞÅ©·Î
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FApplyDamagedComplete);

UCLASS()
class NOAH_API AMapObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMapObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "MapObject")
		float HP;
	UPROPERTY(BlueprintReadWrite, Category = "MapObject")
		UInventory* Inventory;

	UFUNCTION(BlueprintCallable, Category = "MapObject")
		float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);
	
	UPROPERTY(BlueprintAssignable, Category = "MapObject")
		FApplyDamagedComplete ApplyDamagedComplete;
};
