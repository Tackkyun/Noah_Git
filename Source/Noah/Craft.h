// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Item.h"
#include "Craft.generated.h"

USTRUCT(BlueprintType)
struct FSimpleItemStruct {//요구아이템 배열에 들어갈 간단한 형태의 아이템 구조체
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftSimpleItem")
		int ItemCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftSimpleItem")
		int Number;
};

USTRUCT(BlueprintType)
struct FCraftItemStruct { //제작 구조체
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		int ItemCode;//아이템

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		int RequireItemNum;//요구 종류 갯수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		TArray<FSimpleItemStruct> RequireItem;//요구아이템 배열.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		int Price;//가격
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOAH_API UCraft : public UActorComponent
{
	GENERATED_BODY()

public:
	UDataTable* GameObjectLookupTable = nullptr;
	// Sets default values for this component's properties
	UCraft();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		TArray<FCraftItemStruct> CraftList;//제작목록 배열
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		TArray<FCraftItemStruct> CraftListFire;//모닥불 제작목록 배열
};
