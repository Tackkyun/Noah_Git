// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameObject.h"
#include "InstallObjcet.generated.h"

/**
 * 
 */
UCLASS()
class NOAH_API AInstallObject : public AGameObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InstallObject")
		class UStaticMeshComponent* ObjectMeshComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InstallObject")
		FString ObjectName;
public:
	AInstallObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
