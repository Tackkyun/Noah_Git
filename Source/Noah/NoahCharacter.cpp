// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "NoahCharacter.h"


// Sets default values
ANoahCharacter::ANoahCharacter() : m_zoomMax(500), m_zoomMin(200)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 450.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

												// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	Craft = CreateDefaultSubobject<UCraft>(TEXT("Craft"));

	RightEquipmentItem = CreateDefaultSubobject<AItem>(TEXT("RightEquipmentItem"));

	NoahState = ENoahState::IDLE;

	MaxHP = 100.0f;
	HP = 100.0f;
	MaxHungry = 10.0f;
	Hungry = 10.0f;
	MaxTired = 10.0f;
	Tired = 10.0f;

	//상태이상 초기화
	HPUnusualCondition = 0.0f;
	UnusualConditionTickTime = 0.0f;

	LeftEquipmentItem = false;
}

// Called when the game starts or when spawned
void ANoahCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogClass, Log, TEXT("Noah:ANoahCharacter BeginPlay"));
}

// Called every frame
void ANoahCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetCharacterMovement()->IsSwimming()) {
		Tired -= (DeltaTime / 10.0f);
	}
	else {
		Hungry -= (DeltaTime / 30.0f);
		Tired -= (DeltaTime / 30.0f);
	}

	if (Hungry <= 0) {
		HP -= (DeltaTime / 10.0f);
	}
	else if (Tired <= 0) {
		HP -= (DeltaTime / 10.0f);
	}

	UnusualCondition(DeltaTime);
}

// Called to bind functionality to input
void ANoahCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ANoahCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ANoahCharacter::StopJumping);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ANoahCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ANoahCharacter::StopAttack);

	PlayerInputComponent->BindAxis("MoveForward", this, &ANoahCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANoahCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ANoahCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ANoahCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("CameraZoom", this, &ANoahCharacter::CameraZoomRate);
}

void ANoahCharacter::Attack()
{
	if (NoahState == ENoahState::JUMP || NoahState == ENoahState::ATTACK || NoahState == ENoahState::PICKUP ||
		NoahState == ENoahState::EAT || NoahState == ENoahState::DIE) return;
	//PlayAnimMontage();

	NoahState = ENoahState::ATTACK;
}

void ANoahCharacter::StopAttack()
{
	if ( !(NoahState == ENoahState::ATTACK)) return;

	NoahState = ENoahState::ATTACKEND;
}

void ANoahCharacter::Jump()
{
	if (!(NoahState == ENoahState::IDLE || NoahState == ENoahState::RUN) || NoahState == ENoahState::DIE ||
		NoahState == ENoahState::EAT) return;

	NoahState = ENoahState::JUMP;

	bPressedJump = true;
	JumpKeyHoldTime = 0.0f;
}

void ANoahCharacter::StopJumping()
{
	bPressedJump = false;
	ResetJumpState();
}

void ANoahCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ANoahCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ANoahCharacter::MoveForward(float Value)
{
	if (NoahState == ENoahState::PICKUP || NoahState == ENoahState::DIE ||
		NoahState == ENoahState::EAT) return;

	if (GetCharacterMovement()->IsSwimming())
	{
		/*
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		*/
		const FVector CamRotation = CameraBoom->GetForwardVector();

		//FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//AddMovementInput(Direction, Value);

		//FVector Direction = FRotationMatrix(CamRotation).;

		AddMovementInput(CamRotation, Value);

	}
	else if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ANoahCharacter::MoveRight(float Value)
{
	if (NoahState == ENoahState::PICKUP || NoahState == ENoahState::DIE || 
		NoahState == ENoahState::EAT) return;

	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}


void ANoahCharacter::CameraZoomRate(float Rate)
{
	CameraBoom->TargetArmLength += Rate;

	if (CameraBoom->TargetArmLength >= m_zoomMax) {
		CameraBoom->TargetArmLength = m_zoomMax;
	}
	else if (CameraBoom->TargetArmLength <= m_zoomMin) {
		CameraBoom->TargetArmLength = m_zoomMin;
	}
}

bool ANoahCharacter::DetectObject(AActor* detectedObject)
{
	//UE_LOG(LogClass, Log, TEXT("DetectObject %d"), DetectedObject.Num());

	for (int i = 0; i < DetectedObject.Num(); i++) {
		if (DetectedObject[i] == detectedObject) return false; //이미 추가된 Object라면 제외.
	}

	DetectedObject.Add(detectedObject);

	return true;
}

bool ANoahCharacter::MissObject(AActor* missedObject)
{
	for (int i = 0; i < DetectedObject.Num(); i++) {
		if (DetectedObject[i] == missedObject) {
			DetectedObject.RemoveSingle(missedObject); //탐색영역 밖으로 나간 Object 제거.
			return true;
		}
	}

	return false;
}

AActor* ANoahCharacter::FindNearItem()
{
	//예외처리
	if (DetectedObject.Num() <= 0) return nullptr;

	AActor* near = DetectedObject[0]; //가장 가까운 Actor
	FVector playerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(); //캐릭터 위치

	for (int i = 0; i < DetectedObject.Num(); i++) {
		if (FVector::Dist(DetectedObject[i]->GetActorLocation(), playerLocation) < FVector::Dist(near->GetActorLocation(), playerLocation)) { //캐릭터와 가까운 오브젝트 탐색
			near = DetectedObject[i];
		}
	}

	return near;
}

void ANoahCharacter::EquipItem(AItem* _Item)
{
	//AItem* temp = DuplicateObject<AItem>(_Item, this);
	//RightEquipmentItem = temp;
	RightEquipmentItem->InitItem(_Item->ItemCode, 1);
}

TSubclassOf<class UObject> ANoahCharacter::LoadBluePrintClass(FString name)
{
	FString FPath = "Blueprint'/Game/Test/" + name + "." + name + "'";
	const wchar_t* TPath = *FPath;

	UBlueprint* LeftHandEquipment = Cast<UBlueprint>(StaticLoadObject(UObject::StaticClass(), nullptr, TPath));

	return (UClass*)LeftHandEquipment->GeneratedClass;
}

bool ANoahCharacter::ConsumeItem(AItem* _Item, ENoahUnusualCondition _Condition)
{
	if (!(NoahState == ENoahState::IDLE)) return false;

	if (HP + _Item->ThisItem.HpRestore >= MaxHP)
	{
		HP = MaxHP;
	}
	else {
		HP += _Item->ThisItem.HpRestore;
	}

	if (Hungry + _Item->ThisItem.SatietyRestore >= MaxHungry)
	{
		Hungry = MaxHungry;
	}
	else {
		Hungry += _Item->ThisItem.SatietyRestore;
	}

	if (Tired + _Item->ThisItem.ExaustionRestore >= MaxTired)
	{
		Tired = MaxTired;
	}
	else {
		Tired += _Item->ThisItem.ExaustionRestore;
	}

	NoahState = ENoahState::EAT;

	AddUnusualCondition(_Condition);

	return true;
}

float ANoahCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	HP -= ActualDamage;

	if (HP <= 0.0f) {
		NoahState = ENoahState::DIE;
	}
	else
	{
		NoahState = ENoahState::HURT;
	}

	return ActualDamage;
}

//상태이상 추가
void ANoahCharacter::AddUnusualCondition(ENoahUnusualCondition AddCondition)
{
	switch (AddCondition)
	{
	case ENoahUnusualCondition::DEFAULT:
		break;
	case ENoahUnusualCondition::FOODPOISONING:
		FUnusualConditionData TempData;
		TempData.StateName = AddCondition;
		TempData.LifeSpan = 10.0f;
		TempData.Figure = -0.1f;
		HPUnusualCondition += TempData.Figure;
		UnusualConditionArray.Add(TempData);
		break;
	}
}

//상태이상
void  ANoahCharacter::UnusualCondition(float DeltaTime)
{
	if (UnusualConditionArray.Num() > 0) { //상태이상 컨테이너에 아이템이 있으면 작동.
		if (UnusualConditionTickTime < 1.0f) {
			UnusualConditionTickTime += DeltaTime;
		}
		else {
			UnusualConditionTickTime -= 1.0f; //1초마다 적용

			//데미지 적용 및 사망상태
			HP += HPUnusualCondition;
			if (HP <= 0.0f) {
				NoahState = ENoahState::DIE;
			}
		}

		//컨테이너 상태이상 수명 체크
		for (int i = 0; i < UnusualConditionArray.Num(); i++)
		{
			UnusualConditionArray[i].LifeSpan -= DeltaTime;
			if (UnusualConditionArray[i].LifeSpan < 0)//수명이 끝났으면 삭제 
			{
				HPUnusualCondition -= UnusualConditionArray[i].Figure;
				UnusualConditionArray.RemoveAt(i);
				continue;
			}
		}
	}
}

UBlueprintGeneratedClass* ANoahCharacter::GetBlueprint(FString Path)
{
	return LoadObject<UBlueprintGeneratedClass>(nullptr, Path.GetCharArray().GetData());
}