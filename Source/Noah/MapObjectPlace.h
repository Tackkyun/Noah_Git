// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MapObject.h"
#include "MapObjectPlace.generated.h"


//주의 : 블루프린트와 이름이 같아야함 "BP_"제외
UENUM(BlueprintType)
enum class EMapObjectEnum : uint8
{
	Tree		UMETA(DisplayName="Tree"),
	Stone		UMETA(DisplayName="Stone")
};

USTRUCT(BlueprintType)
struct FMapObjectPlaceStruct {
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MapObjectPlace")
		EMapObjectEnum MapObject;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MapObjectPlace")
		int Number;
};

UCLASS()
class NOAH_API AMapObjectPlace : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "MapObjectPlace")
		UBoxComponent* Place;
	UPROPERTY(BlueprintReadWrite, Category = "MapObjectPlace")
		USphereComponent* PlaceSphere;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MapObjectPlace")
		TArray<FMapObjectPlaceStruct> MapObjectList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MapObjectPlace")
		bool bSpherePlace;
public:	
	// Sets default values for this actor's properties
	AMapObjectPlace();

	UFUNCTION(BlueprintCallable, Category = "MapObjectPlace")
		UBlueprintGeneratedClass* ObjectPathSeek(EMapObjectEnum objectType);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void FindRandomPlaceLine(bool bPlaceType, FVector& startLine, FVector& endLine);
	void SpawnRandomPlace(bool bPlaceType);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
