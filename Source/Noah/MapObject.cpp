// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "MapObject.h"


// Sets default values
AMapObject::AMapObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	HP = 30.0f;
}

// Called when the game starts or when spawned
void AMapObject::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMapObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AMapObject::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	HP -= ActualDamage;

	ApplyDamagedComplete.Broadcast();

	return ActualDamage;
}