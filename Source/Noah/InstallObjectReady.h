// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InstallObjcet.h"
#include "InstallObjectReady.generated.h"

UCLASS()
class NOAH_API AInstallObjectReady : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "InstallObjectReady")
		UStaticMeshComponent* ObjectMeshComponent;
	UPROPERTY(BlueprintReadWrite, Category = "InstallObjectReady")
		FVector InstallLocation;
	UPROPERTY(BlueprintReadWrite, Category = "InstallObjectReady")
		FRotator InstallRotator;
	UPROPERTY(BlueprintReadWrite, Category = "InstallObjectReady")
		float ObjectRot;
private:
	bool m_bInstallReady; //설치가 가능하다면 TRUE, 아니라면 FALSE

public:
	// Sets default values for this actor's properties
	AInstallObjectReady();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "InstallObjectReady")
		bool InstallTest(float degreeRange, float forwardDist, float downDist);

	UFUNCTION(BlueprintCallable, Category = "InstallObjectReady")
		AInstallObject* SpawnInstallObject(FString str, FVector spawnLocation, FRotator spawnRotator);
	UFUNCTION(BlueprintCallable, Category = "InstallObjectReady")
		UStaticMesh* SetInstallStaticMesh(FString str);
};
