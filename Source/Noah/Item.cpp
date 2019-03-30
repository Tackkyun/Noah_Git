// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "Item.h"


// Sets default values
AItem::AItem() : Number(0), CurrentDurability(-1), ItemCode(-1)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitItem(-1);

	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMeshComponent;

	UE_LOG(LogClass, Log, TEXT("Noah:AItem Init"));
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogClass, Log, TEXT("Noah:AItem BeginPlay"));
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AItem* AItem::InitItem(int32 itemCode, int32 number /*= 1*/)
{
	if (itemCode == 0) return nullptr;
	

	if (itemCode == -1) {
		this->ItemCode = itemCode;
		this->Number = 0;
		ThisItem.NameCode = "";
		ThisItem.Name = "";
		ThisItem.Explanation = "";
		ThisItem.HandType = 0;
		ThisItem.Arrange = 0;
		ThisItem.Consume = 0;
		ThisItem.Parts = 0;
		ThisItem.Endurance = 0;
		ThisItem.Trade = "";
		ThisItem.GatherPower = 0;
		ThisItem.AttackPower = 0;
		ThisItem.HpRestore = 0;
		ThisItem.SatietyRestore = 0;
		ThisItem.ExaustionRestore = 0;
		ThisItem.ApplyCondition = "";
		ThisItem.Recipe = "";
		ThisItem.WorldImgCode = "";
		ThisItem.InvenImgCode = "";
		ThisItem.HitSE = "";
		ThisItem.HitVE = "";
		ThisItem.EquipSE = "";
		ThisItem.IsEnd = "";
	}
	else {
		//생성자에서만 작동. 하단 LoadObject로 대체
		//static ConstructorHelpers::FObjectFinder<UDataTable>
		//	GameObjectLookupDataTable_BP(TEXT("DataTable'/Game/DataTable/DT_Item.DT_Item'"));
		//UDataTable* GameObjectLookupTable = GameObjectLookupDataTable_BP.Object;
		//FString ContextString;
		//ThisItem = *GameObjectLookupTable->FindRow<FItemStruct>(FName(*FString::FromInt(itemCode)), ContextString);
		
		//DataTable에서 해당 코드의 item 정보를 받아 넣음.
		this->ItemCode = itemCode;
		this->Number = number;
		UDataTable* GameObjectLookupTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/DataTable/DT_Item.DT_Item'"));
		FString ContextString;
		ThisItem = *GameObjectLookupTable->FindRow<FItemStruct>(FName(*FString::FromInt(itemCode)), ContextString);
		return this;
	}
	return this;
}

UTexture2D* AItem::GetItemImage(FString imageName)
{
	FString FileName = "/Game/Resource/Img/";
	FString FullName = FileName + imageName + "." + imageName;

	return LoadObject<UTexture2D>(nullptr, FullName.GetCharArray().GetData());
}

UStaticMesh* AItem::GetItemStaticMesh(FString StaticMeshName)
{
	FString FileName = "/Game/Resource/Mesh/";
	FString FullName = FileName + StaticMeshName + "." + StaticMeshName;

	return LoadObject<UStaticMesh>(nullptr, FullName.GetCharArray().GetData());
}

void AItem::SetMesh()
{
	//예외처리
	if (ItemCode <= 0) return;

	//Mesh루트
	FString FileName = "/Game/Resource/Mesh/";
	FString FullName = FileName + ThisItem.WorldImgCode + "." + ThisItem.WorldImgCode;

	//Mesh생성 및 세팅
	ItemMeshComponent->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, FullName.GetCharArray().GetData()));
	ItemMeshComponent->SetVisibility(true);
	ItemMeshComponent->RegisterComponent();

	ItemMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	ItemMeshComponent->SetMobility(EComponentMobility::Movable);
	ItemMeshComponent->SetRelativeLocation(FVector(0, 0, 0));
	ItemMeshComponent->SetRelativeRotation(FRotator::ZeroRotator);
	ItemMeshComponent->SetRelativeScale3D(FVector(1, 1, 1));
	ItemMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	ItemMeshComponent->SetSimulatePhysics(true);
	ItemMeshComponent->SetEnableGravity(true);
	ItemMeshComponent->bGenerateOverlapEvents = true;
}
