// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "NaturalEnvironment.h"


// Sets default values
ANaturalEnvironment::ANaturalEnvironment() : SunDrive(0.f), DayDuration(0.f), MaxSunHeight(0.f), DirectionLight(nullptr), SkySphere(nullptr),
SkyLight(nullptr), CurveSkyLightColor(nullptr), CurveOverallColor(nullptr), CurveHorizonColor(nullptr), CurveZenithColor(nullptr), CurveSunIntensity(nullptr),
RainValue(0.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UCurveLinearColor> SkyLightColor(TEXT("CurveLinearColor'/Game/MapEnvironment/Curve_SkyLightColor.Curve_SkyLightColor'"));
	if (SkyLightColor.Succeeded()) {
		CurveSkyLightColor = SkyLightColor.Object;
	}
	ConstructorHelpers::FObjectFinder<UCurveLinearColor> OverallColor(TEXT("CurveLinearColor'/Game/MapEnvironment/Curve_SkySphere_OverallColor.Curve_SkySphere_OverallColor'"));
	if (OverallColor.Succeeded()) {
		CurveOverallColor = OverallColor.Object;
	}
	ConstructorHelpers::FObjectFinder<UCurveLinearColor> HorizonColor(TEXT("CurveLinearColor'/Engine/EngineSky/C_Sky_Horizon_Color.C_Sky_Horizon_Color'"));
	if (HorizonColor.Succeeded()) {
		CurveHorizonColor = HorizonColor.Object;
	}
	ConstructorHelpers::FObjectFinder<UCurveLinearColor> ZenithColor(TEXT("CurveLinearColor'/Engine/EngineSky/C_Sky_Zenith_Color.C_Sky_Zenith_Color'"));
	if (ZenithColor.Succeeded()) {
		CurveZenithColor = ZenithColor.Object;
	}
	ConstructorHelpers::FObjectFinder<UCurveFloat> SunIntensity(TEXT("CurveFloat'/Game/MapEnvironment/Curve_SunIntensity.Curve_SunIntensity'"));
	if (SunIntensity.Succeeded()) {
		CurveSunIntensity = SunIntensity.Object;
	}
}

// Called when the game starts or when spawned
void ANaturalEnvironment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANaturalEnvironment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FRotator ANaturalEnvironment::SeekSunRotator(float _sunDrive, float _dayDuration, float _maxSunHeight)
{
	float pitch = FMath::Sin((((_sunDrive / _dayDuration) * 2) * PI)) * _maxSunHeight;
	float yaw = (_sunDrive * 360) / _dayDuration;
	FRotator rot(pitch, yaw, 0.f);

	return rot;
}
