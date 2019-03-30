// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "Inventory.h"
#include <queue>


// Sets default values for this component's properties
UInventory::UInventory() : MaxInvenSize(16), CurrentWeight(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	UE_LOG(LogClass, Log, TEXT("Noah:UInventory Init"));
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	//인벤토리 초기화
	for (int i = 0; i < MaxInvenSize; ++i) {
		ItemList.Add(NewObject<AItem>(this));
	}
	
	UE_LOG(LogClass, Log, TEXT("Noah:UInventory BeginPlay"));
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventory::AddItem(AItem* item)
{
	for (int i = 0; i < MaxInvenSize; i++) {
		if (ItemList[i]->ItemCode == item->ItemCode) {
			ItemList[i]->Number += item->Number;
			AddItemCompleteDelegate.Broadcast(); //Delgate 발행. 모든 구독자들(UI 등)에게 이벤트를 발생.
			return true;
		}
	}

	//아이템이 비어있을 경우 추가. 그렇지 않으면 return false
	for (int i = 0; i < MaxInvenSize; i++) {
		if (ItemList[i]->ItemCode == -1) {
			AItem* temp = DuplicateObject<AItem>(item, this);
			ItemList[i] = temp;
			ItemList[i]->InitItem(ItemList[i]->ItemCode, item->Number); //Datatable에서 정보 넣기.
			AddItemCompleteDelegate.Broadcast(); //Delgate 발행. 모든 구독자들(UI 등)에게 이벤트를 발생.
			return true;
		}
	}

	return false;
}

bool UInventory::RemoveItemNumber(int32 index, int32 number)
{
	for (int i = 0; i < MaxInvenSize; i++) {
		if (ItemList[i]->ItemCode == index) {
			if (ItemList[i]->Number > number) {
				ItemList[i]->Number -= number;
				AddItemCompleteDelegate.Broadcast();
				return true;
			}
			else if (ItemList[i]->Number == number) {
				ItemList[i]->Number = 0;
				ItemList[i]->ItemCode = -1;
				ItemList[i]->InitItem(-1);
				AddItemCompleteDelegate.Broadcast();
				return true;
			}
			else {
				return false;
			}
		}
	}

	return false;
}

bool UInventory::RemoveItemInventorySlot(int32 index, int32 number)
{
	//예외처리
	if (index < 0 || index >= MaxInvenSize) return false;

	if (ItemList[index]->Number > number) {
		ItemList[index]->Number -= number;
		AddItemCompleteDelegate.Broadcast();
		return true;
	}
	else {
		ItemList[index]->Number = 0;
		ItemList[index]->ItemCode = -1;
		ItemList[index]->InitItem(-1);
		AddItemCompleteDelegate.Broadcast();
		return true;
	}

	return false;
}


bool UInventory::SwapItemIndex(int32 left, int32 right)
{
	//예외처리
	if (left < 0 || left >= MaxInvenSize ||
		right < 0 || right >= MaxInvenSize) return false;

	Swap(ItemList[left], ItemList[right]);

	return true;
}

void UInventory::SortInventory()
{
	std::queue<int> tempSlot;

	//Queue에 빈 슬롯을 넣어, 아이템과 빈슬롯을 Swap.
	for (int i = 0; i < MaxInvenSize; i++) {
		if (ItemList[i]->ItemCode == -1) {
			tempSlot.push(i);
		}
		else if (!tempSlot.empty()) {
			if (SwapItemIndex(i, tempSlot.front())) {
				tempSlot.pop();
				tempSlot.push(i);
			}
		}
	}

	AddItemCompleteDelegate.Broadcast(); //UI갱신 호출.
}

int UInventory::GetItemNumberInfo(int _itemIndex)
{
	for (int i = 0; i < MaxInvenSize; i++) {
		if (ItemList[i]->ItemCode == _itemIndex) {
			return ItemList[i]->Number;
		}
	}

	return 0;
}

//아이템 스폰
void UInventory::SpawnItem(AItem* CreatedItem, FVector SpawnLocation)
{
	//AItem* Item = GetWorld()->SpawnActor<AItem>(GetClass(), SpawnLocation, FRotator::ZeroRotator);
	//Item = CreatedItem;
	
}