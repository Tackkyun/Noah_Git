// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Ark.generated.h"

USTRUCT(BlueprintType)
struct FArkRequireItemStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Ark")
		int32 RequireItemCode;
	UPROPERTY(BlueprintReadWrite, Category = "Ark")
		int32 Number;
};

USTRUCT(BlueprintType)
struct FArkLevelStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Ark")
		int32 Level;
	UPROPERTY(BlueprintReadOnly, Category = "Ark")
		TArray<FArkRequireItemStruct> ArkRequireItems;
};

UCLASS()
class NOAH_API AArk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "Ark")
		TArray<FArkLevelStruct> ArkRequire;
	UPROPERTY(BlueprintReadWrite, Category = "Ark")
		TArray<FArkLevelStruct> ArkHaveItem;

	UFUNCTION(BlueprintCallable, Category = "Ark")
		UStaticMesh* GetArkStaticMesh(FString Path);
	UFUNCTION(BlueprintCallable, Category = "Ark")
		UTexture2D* GetArkRequireItemImage(FString Path);

	UFUNCTION(BlueprintCallable, Category = "Ark")
		bool AddItem(int32 Level, int32 Index, int32 Number);
};
