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

	//�÷��̾� ĳ���� �տ��� 200������ ��ġ
	FVector StartLine = (PlayerPawn->GetActorForwardVector() * forwardDist) + PlayerPawn->GetActorLocation();
	StartLine.Z += 50;
	FVector EndLine = FVector(StartLine.X, StartLine.Y, StartLine.Z - downDist);

	//������ �Ʒ��� Line�� ���ؼ� �ѵ��Ǵ� �������� �����ش�.
	FHitResult outHit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(outHit, StartLine, EndLine, ECC_Visibility);
	//NormalVector�� �������� ������Ʈ ȸ��.
	FRotator normalRot = FRotationMatrix::MakeFromZ(outHit.Normal).Rotator();

	//NormalVector������ �������� ȸ��
	FRotator axisNormalRot = UKismetMathLibrary::RotatorFromAxisAndAngle(outHit.Normal, ObjectRot);
	FTransform axisNormalTransform(axisNormalRot);
	FTransform normalRotTransform(normalRot);
	//NormalVector������ �������� ȸ���� ��İ� ormalVector�� �������� ������Ʈ ȸ���� ����� �����ش�.
	FTransform finalTrnasform = normalRotTransform*axisNormalTransform;

	SetActorLocation(outHit.Location);
	SetActorRotation(finalTrnasform.Rotator());
	//InstallObject ���� �� �ʿ��� ���� ����.
	InstallLocation = outHit.Location;
	InstallRotator = finalTrnasform.Rotator();

	//NormalVector�� Z��� ����
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