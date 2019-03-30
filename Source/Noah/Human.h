// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NPC.h"
#include "Human.generated.h"

/**
 * 
 */
UCLASS()
class NOAH_API AHuman : public ANPC
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Human")
		FString Name;
public:
	AHuman();
	
	
	
};
