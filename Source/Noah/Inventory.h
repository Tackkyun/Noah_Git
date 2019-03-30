// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Item.h"
#include "Inventory.generated.h"

//Delegate 메크로
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAddItemCompleteDelegate);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NOAH_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Delegate 변수
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FAddItemCompleteDelegate AddItemCompleteDelegate;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		TArray<AItem *> ItemList;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		int32 CurrentWeight; //현재 아이템 총 무게
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		int32 MaxInvenSize; //최대 아이템 슬롯 수
	//int32 CurrentInvenSize; //현재 사용중인 아이템 슬롯 수

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool AddItem(AItem* item); //인벤토리에 아이템 추가
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool RemoveItemNumber(int32 index, int32 number); //인벤토리에 아이템 제거. 아이템 인덱스, 갯수
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool RemoveItemInventorySlot(int32 index, int32 number); //인벤토리에 아이템 제거. 인벤토리 인덱스, 갯수
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool SwapItemIndex(int32 left, int32 right); //아이템 교체
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void SortInventory(); //아이템 정렬
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		int GetItemNumberInfo(int _itemIndex); //특정 아이템 개수 얻기
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void SpawnItem(AItem* CreatedItem, FVector SpawnLocation);
};
