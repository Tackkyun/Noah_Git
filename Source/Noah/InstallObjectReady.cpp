// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "InstallObjectReady.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

// Sets default values
AInstallObjectReady::AInstallObjectReady() : ObjectRot(0.f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ObjectMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	RootComponent = ObjectMeshComponent;

	ObjectMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AInstallObjectReady::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInstallObjectReady::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

bool AInstallObjectReady::InstallTest(float degreeRange, float forwardDist, float downDist)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	//플레이어 캐릭터 앞에서 200떨어진 위치
	FVector StartLine = (PlayerPawn->GetActorForwardVector() * forwardDist) + PlayerPawn->GetActorLocation();
	StartLine.Z += 50;
	FVector EndLine = FVector(StartLine.X, StartLine.Y, StartLine.Z - downDist);

	//위에서 아래로 Line을 통해서 총돌되는 정보들을 얻어와준다.
	FHitResult outHit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(outHit, StartLine, EndLine, ECC_Visibility);
	//NormalVector의 방향으로 오브젝트 회전.
	FRotator normalRot = FRotationMatrix::MakeFromZ(outHit.Normal).Rotator();

	//NormalVector방향을 기준으로 회전
	FRotator axisNormalRot = UKismetMathLibrary::RotatorFromAxisAndAngle(outHit.Normal, ObjectRot);
	FTransform axisNormalTransform(axisNormalRot);
	FTransform normalRotTransform(normalRot);
	//NormalVector방향을 기준으로 회전한 행렬과 ormalVector의 방향으로 오브젝트 회전한 행렬을 얻어와준다.
	FTransform finalTrnasform = normalRotTransform*axisNormalTransform;

	SetActorLocation(outHit.Location);
	SetActorRotation(finalTrnasform.Rotator());
	//InstallObject 스폰 시 필요한 정보 저장.
	InstallLocation = outHit.Location;
	InstallRotator = finalTrnasform.Rotator();

	//NormalVector와 Z축과 내적
	float degree = UKismetMathLibrary::Dot_VectorVector(FVector(0, 0, 1), outHit.Normal);
	if (degree >= degreeRange) {
		return true;
	}
	else {
		return false;
	}
}

AInstallObject* AInstallObjectReady::SpawnInstallObject(FString str, FVector spawnLocation, FRotator spawnRotator)
{
	FString blueprintName = "BP_" + str;
	FString path = "/Game/Object/InstallObject/" + blueprintName + "." + blueprintName + "_C";
	UBlueprintGeneratedClass * BPGC = LoadObject<UBlueprintGeneratedClass>(nullptr, path.GetCharArray().GetData());

	AInstallObject* obj= GetWorld()->SpawnActor<AInstallObject>(BPGC, spawnLocation, spawnRotator);
	return obj;
}

UStaticMesh* AInstallObjectReady::SetInstallStaticMesh(FString str)
{
	FString meshName = "Mesh_" + str;
	FString path = "/Game/Resource/Mesh/" + meshName + "." + meshName;
	UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr, path.GetCharArray().GetData());
	ObjectMeshComponent->SetStaticMesh(mesh);

	return mesh;
}