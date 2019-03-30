// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Item.h"
#include "Craft.generated.h"

USTRUCT(BlueprintType)
struct FSimpleItemStruct {//�䱸������ �迭�� �� ������ ������ ������ ����ü
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftSimpleItem")
		int ItemCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftSimpleItem")
		int Number;
};

USTRUCT(BlueprintType)
struct FCraftItemStruct { //���� ����ü
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		int ItemCode;//������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		int RequireItemNum;//�䱸 ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		TArray<FSimpleItemStruct> RequireItem;//�䱸������ �迭.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		int Price;//����
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
		TArray<FCraftItemStruct> CraftList;//���۸�� �迭
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		TArray<FCraftItemStruct> CraftListFire;//��ں� ���۸�� �迭
};
