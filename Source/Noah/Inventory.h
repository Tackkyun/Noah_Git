// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Item.h"
#include "Inventory.generated.h"

//Delegate ��ũ��
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

	//Delegate ����
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FAddItemCompleteDelegate AddItemCompleteDelegate;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		TArray<AItem *> ItemList;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		int32 CurrentWeight; //���� ������ �� ����
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		int32 MaxInvenSize; //�ִ� ������ ���� ��
	//int32 CurrentInvenSize; //���� ������� ������ ���� ��

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool AddItem(AItem* item); //�κ��丮�� ������ �߰�
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool RemoveItemNumber(int32 index, int32 number); //�κ��丮�� ������ ����. ������ �ε���, ����
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool RemoveItemInventorySlot(int32 index, int32 number); //�κ��丮�� ������ ����. �κ��丮 �ε���, ����
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool SwapItemIndex(int32 left, int32 right); //������ ��ü
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void SortInventory(); //������ ����
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		int GetItemNumberInfo(int _itemIndex); //Ư�� ������ ���� ���
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void SpawnItem(AItem* CreatedItem, FVector SpawnLocation);
};
