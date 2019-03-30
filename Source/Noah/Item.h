// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Item.generated.h"


//DataTable �׸� ���� ����ü ����
USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		FString NameCode;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		FString Name;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		FString Explanation;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		int32 HandType;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		int32 Arrange;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		int32 Consume;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		int32  Parts;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		int32 Endurance;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		FString Trade;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		int32 GatherPower;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		int32 AttackPower;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		int32 HpRestore;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		int32 SatietyRestore;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		int32 ExaustionRestore;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		FString ApplyCondition;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		FString Recipe;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		FString WorldImgCode;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		FString InvenImgCode;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		FString HitSE;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		FString HitVE;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		FString EquipSE;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		FString IsEnd;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		int32 Craft;
	UPROPERTY(BlueprintReadOnly, Category = "ItemInformation")
		int32 Install;
};

UCLASS()
class NOAH_API AItem : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION(BlueprintCallable, Category = "ItemClass")
		AItem* InitItem(int32 itemCode, int32 number = 1);
	UFUNCTION(BlueprintCallable, Category = "ItemClass")
		UTexture2D* GetItemImage(FString imageName); //�ش� ������ �̹����ؽ�ó ������
	UFUNCTION(BlueprintCallable, Category = "ItemClass")
		UStaticMesh* GetItemStaticMesh(FString StaticMeshName); //�ش� ������ �޽� ������
	UFUNCTION(BlueprintCallable, Category = "ItemClass")
		void SetMesh(); //����� Drop�� �ʿ��� �޽� ���� �� ����

public:
	UPROPERTY(BlueprintReadWrite, Category = "ItemClass")
	FItemStruct ThisItem;
	UPROPERTY(BlueprintReadWrite, Category = "ItemClass")
	int32 Number; //����
	UPROPERTY(BlueprintReadWrite, Category = "ItemClass")
	int32 CurrentDurability; //���� ������.
	UPROPERTY(BlueprintReadWrite, Category = "ItemClass")
	int32 ItemCode; //������ ���̺��� ������ �ڵ�.

	UPROPERTY(BlueprintReadWrite, Category = "ItemClass")
	class UStaticMeshComponent* ItemMeshComponent;
};
