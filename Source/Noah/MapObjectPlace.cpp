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
	//���� �� ������Ʈ�� ��θ� �ҷ����ش�.
	
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMapObjectEnum"), true);
	FString blueprintName = "BP_" + EnumPtr->GetEnumNameStringByValue((int32)objectType);
	FString path = "/Game/MapObject/" + blueprintName + "." + blueprintName + "_C";

	//����� �̸��� �߸��Ǿ��ų� ��ü�� ���ٸ� nullptr��  ��ȯ�ȴ�.
	UBlueprintGeneratedClass *BPGC = LoadObject<UBlueprintGeneratedClass>(nullptr, path.GetCharArray().GetData());
	return BPGC;
}

void AMapObjectPlace::FindRandomPlaceLine(bool bPlaceType, FVector& startLine, FVector& endLine)
{
	if (bPlaceType == true) { //Sphere ������ Spawn�Ѵٸ�.
		//������ �Ÿ��� ������ �����ش�..
		FVector distance(FMath::FRandRange(0.f, PlaceSphere->GetScaledSphereRadius()), 0, 0);
		FVector dir = distance.RotateAngleAxis(FMath::FRandRange(0.f, 360.f), FVector(0, 0, 1));

		startLine = FVector(this->GetActorLocation().X + dir.X, this->GetActorLocation().Y + dir.Y,
			this->GetActorLocation().Z + Place->GetScaledBoxExtent().Z);
		endLine = FVector(startLine.X, startLine.Y,
			this->GetActorLocation().Z + (Place->GetScaledBoxExtent().Z * (-1)));
	}
	else { //Box  ������ Spawn�Ѵٸ�
		   //���� ��ǥ�� �����ش�.
		startLine = FVector(
			FMath::FRandRange(-1000, 1000),
			FMath::FRandRange(-1000, 1000),
			1000);

		//����� ���� ������ǥ�� �̵������ش�.(Box ������ ȸ��, �̵�, ������ ����Ǳ� ���� �۾�)
		startLine = UKismetMathLibrary::TransformLocation(this->GetTransform(), startLine);
		endLine = FVector(startLine.X, startLine.Y, this->GetActorLocation().Z + (Place->GetScaledBoxExtent().Z * (-1)));
	}
}

void AMapObjectPlace::SpawnRandomPlace(bool bPlaceType)
{
	for (int i = 0; i < MapObjectList.Num(); ++i)
	{
		//���� �� ������Ʈ�� �ҷ����ش�.
		UBlueprintGeneratedClass *BPGC = ObjectPathSeek(MapObjectList[i].MapObject);

		if (BPGC != nullptr) { //����� �̸��� �߸��Ǿ��ų� ��ü�� ���ٸ� ����ȴ�.
			for (int j = 0; j < MapObjectList[i].Number; ++j) {

				FVector StartLine(0, 0, 0);
				FVector EndLine(0, 0, 0);
				//���� �������� �˻� �� Line�� ���� �����ش�.
				FindRandomPlaceLine(bPlaceType, StartLine, EndLine);

				//������ �Ʒ��� Line�� ���ؼ� �ѵ��Ǵ� �������� �����ش�.
				FHitResult outHit(ForceInit);
				GetWorld()->LineTraceSingleByChannel(outHit, StartLine, EndLine, ECC_WorldStatic);

				if (outHit.GetActor() != nullptr) { //Hit�Ǵ� ���Ͱ� �����Ѵٸ� ����ȴ�.
					if (outHit.GetActor()->ActorHasTag("Landscape")) { //Hit�Ǵ� ���Ͱ� Landscape���߸� ����ȴ�.
						float degree = UKismetMathLibrary::Dot_VectorVector(FVector(0, 0, 1), outHit.Normal);
						if (degree >= 0.9f) { //������Ʈ�� ���� ���� �̻����� ���̸� �ȱ׷�����.
							FRotator rot = FRotationMatrix::MakeFromZ(outHit.Normal).Rotator();
							//���忡 ������Ʈ�� �������ش�.
							GetWorld()->SpawnActor<AActor>(BPGC, outHit.Location, rot);
						}
					}
				}
			}
		}
	}
}