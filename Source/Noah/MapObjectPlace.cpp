// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "MapObjectPlace.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

// Sets default values
AMapObjectPlace::AMapObjectPlace() : Place(nullptr), PlaceSphere(nullptr), bSpherePlace(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Place = CreateDefaultSubobject<UBoxComponent>(TEXT("Place"));
	RootComponent = Place;
	Place->SetBoxExtent(FVector(1000, 1000, 1000));
	Place->ShapeColor = FColor(255, 0, 0, 255);
	
	PlaceSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlaceSphere"));
	PlaceSphere->AttachTo(Place);
	PlaceSphere->SetSphereRadius(1000.f);
	PlaceSphere->ShapeColor = FColor(255, 0, 0, 255);
}

// Called when the game starts or when spawned
void AMapObjectPlace::BeginPlay()
{
	Super::BeginPlay();

	SpawnRandomPlace(bSpherePlace);
}

// Called every frame
void AMapObjectPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBlueprintGeneratedClass* AMapObjectPlace::ObjectPathSeek(EMapObjectEnum objectType)
{
	//스폰 할 오브젝트의 경로를 불러와준다.
	
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMapObjectEnum"), true);
	FString blueprintName = "BP_" + EnumPtr->GetEnumNameStringByValue((int32)objectType);
	FString path = "/Game/MapObject/" + blueprintName + "." + blueprintName + "_C";

	//경로의 이름이 잘못되었거나 객체가 없다면 nullptr이  반환된다.
	UBlueprintGeneratedClass *BPGC = LoadObject<UBlueprintGeneratedClass>(nullptr, path.GetCharArray().GetData());
	return BPGC;
}

void AMapObjectPlace::FindRandomPlaceLine(bool bPlaceType, FVector& startLine, FVector& endLine)
{
	if (bPlaceType == true) { //Sphere 영역에 Spawn한다면.
		//임의의 거리와 방향을 구해준다..
		FVector distance(FMath::FRandRange(0.f, PlaceSphere->GetScaledSphereRadius()), 0, 0);
		FVector dir = distance.RotateAngleAxis(FMath::FRandRange(0.f, 360.f), FVector(0, 0, 1));

		startLine = FVector(this->GetActorLocation().X + dir.X, this->GetActorLocation().Y + dir.Y,
			this->GetActorLocation().Z + Place->GetScaledBoxExtent().Z);
		endLine = FVector(startLine.X, startLine.Y,
			this->GetActorLocation().Z + (Place->GetScaledBoxExtent().Z * (-1)));
	}
	else { //Box  영역에 Spawn한다면
		   //로컬 좌표로 구해준다.
		startLine = FVector(
			FMath::FRandRange(-1000, 1000),
			FMath::FRandRange(-1000, 1000),
			1000);

		//행렬을 곱해 월드좌표로 이동시켜준다.(Box 영역이 회전, 이동, 변형이 적용되기 위한 작업)
		startLine = UKismetMathLibrary::TransformLocation(this->GetTransform(), startLine);
		endLine = FVector(startLine.X, startLine.Y, this->GetActorLocation().Z + (Place->GetScaledBoxExtent().Z * (-1)));
	}
}

void AMapObjectPlace::SpawnRandomPlace(bool bPlaceType)
{
	for (int i = 0; i < MapObjectList.Num(); ++i)
	{
		//스폰 할 오브젝트를 불러와준다.
		UBlueprintGeneratedClass *BPGC = ObjectPathSeek(MapObjectList[i].MapObject);

		if (BPGC != nullptr) { //경로의 이름이 잘못되었거나 객체가 없다면 실행된다.
			for (int j = 0; j < MapObjectList[i].Number; ++j) {

				FVector StartLine(0, 0, 0);
				FVector EndLine(0, 0, 0);
				//선택 영역에서 검사 할 Line의 값을 얻어와준다.
				FindRandomPlaceLine(bPlaceType, StartLine, EndLine);

				//위에서 아래로 Line을 통해서 총돌되는 정보들을 얻어와준다.
				FHitResult outHit(ForceInit);
				GetWorld()->LineTraceSingleByChannel(outHit, StartLine, EndLine, ECC_WorldStatic);

				if (outHit.GetActor() != nullptr) { //Hit되는 엑터가 존재한다면 실행된다.
					if (outHit.GetActor()->ActorHasTag("Landscape")) { //Hit되는 엑터가 Landscape여야만 실행된다.
						float degree = UKismetMathLibrary::Dot_VectorVector(FVector(0, 0, 1), outHit.Normal);
						if (degree >= 0.9f) { //오브젝트가 일정 각도 이상으로 꺾이면 안그려진다.
							FRotator rot = FRotationMatrix::MakeFromZ(outHit.Normal).Rotator();
							//월드에 오브젝트를 스폰해준다.
							GetWorld()->SpawnActor<AActor>(BPGC, outHit.Location, rot);
						}
					}
				}
			}
		}
	}
}