// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "Ark.h"


// Sets default values
AArk::AArk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArk::BeginPlay()
{
	Super::BeginPlay();
	
	FArkLevelStruct TempArkLevelStruct;
	FArkRequireItemStruct TempArkRequireItemStruct;

	//================================ level0
	TempArkLevelStruct.Level = 0;
	//==========
	TempArkRequireItemStruct.RequireItemCode	= 1;
	TempArkRequireItemStruct.Number				= 10;
	TempArkLevelStruct.ArkRequireItems.Add(TempArkRequireItemStruct);

	TempArkRequireItemStruct.RequireItemCode	= 2;
	TempArkRequireItemStruct.Number				= 10;
	TempArkLevelStruct.ArkRequireItems.Add(TempArkRequireItemStruct);
	//==========
	ArkRequire.Add(TempArkLevelStruct);
	ArkHaveItem.Add(TempArkLevelStruct);
	TempArkLevelStruct.ArkRequireItems.Empty();
	//================================ level0 end


	//================================ level1
	TempArkLevelStruct.Level = 1;
	//==========
	TempArkRequireItemStruct.RequireItemCode = 1;
	TempArkRequireItemStruct.Number = 10;
	TempArkLevelStruct.ArkRequireItems.Add(TempArkRequireItemStruct);

	TempArkRequireItemStruct.RequireItemCode = 3;
	TempArkRequireItemStruct.Number = 10;
	TempArkLevelStruct.ArkRequireItems.Add(TempArkRequireItemStruct);
	//==========
	ArkRequire.Add(TempArkLevelStruct);
	ArkHaveItem.Add(TempArkLevelStruct);
	TempArkLevelStruct.ArkRequireItems.Empty();
	//================================ level1 end


	//================================ level2
	TempArkLevelStruct.Level = 2;
	//==========
	TempArkRequireItemStruct.RequireItemCode = 1;
	TempArkRequireItemStruct.Number = 10;
	TempArkLevelStruct.ArkRequireItems.Add(TempArkRequireItemStruct);

	TempArkRequireItemStruct.RequireItemCode = 2;
	TempArkRequireItemStruct.Number = 10;
	TempArkLevelStruct.ArkRequireItems.Add(TempArkRequireItemStruct);
	//==========
	ArkRequire.Add(TempArkLevelStruct);
	ArkHaveItem.Add(TempArkLevelStruct);
	TempArkLevelStruct.ArkRequireItems.Empty();
	//================================ level2 end

	//갖고있는 아이템 갯수 초기화
	for (int i = 0; i < ArkHaveItem.Num(); i++) {
		for (int j = 0; j < ArkHaveItem[i].ArkRequireItems.Num(); j++) {
			ArkHaveItem[i].ArkRequireItems[j].Number = 0;
		}
	}
}

// Called every frame
void AArk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


UStaticMesh* AArk::GetArkStaticMesh(FString Path)
{
	//FString FileName = "/Game/Resource/Mesh/";
	//FString FullName = FileName + StaticMeshName + "." + StaticMeshName;

	return LoadObject<UStaticMesh>(nullptr, Path.GetCharArray().GetData());
}

UTexture2D* AArk::GetArkRequireItemImage(FString Path)
{
	return LoadObject<UTexture2D>(nullptr, Path.GetCharArray().GetData());
}

bool AArk::AddItem(int32 Level, int32 Index, int32 Number)
{
	ArkHaveItem[Level].ArkRequireItems[Index].Number += Number;

	if (ArkHaveItem[Level].ArkRequireItems[Index].Number == ArkRequire[Level].ArkRequireItems[Index].Number) {
		return true;
	}
	else {
		return false;
	}
}