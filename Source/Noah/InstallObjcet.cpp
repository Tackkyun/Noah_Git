// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "InstallObjcet.h"


AInstallObject::AInstallObject()
{
	ObjectMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	RootComponent = ObjectMeshComponent;
}

// Called when the game starts or when spawned
void AInstallObject::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInstallObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}