// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Inventory.h"
#include "Craft.h"
#include "Item.h"
#include "NoahCharacter.generated.h"

UENUM(BlueprintType)
enum class ENoahState : uint8
{
	IDLE	UMETA(DisplayName = "IDLE"),
	RUN		UMETA(DisplayName = "RUN"),
	JUMP	UMETA(DisplayName = "JUMP"),
	ATTACK	UMETA(DisplayName = "ATTACK"),
	ATTACKEND UMETA(DisplayName = "ATTACKEND"),
	DIE		UMETA(DisplayName = "DIE"),
	SWIM	UMETA(DisplayName = "SWIM"),
	PICKUP	UMETA(DisplayName = "PICKUP"),
	EAT		UMETA(DisplayName = "EAT"),
	HURT	UMETA(DisplayName = "HURT")
};

UENUM(BlueprintType)
enum class ENoahUnusualCondition : uint8
{
	DEFAULT			UMETA(DisplayName = "DEFAULT"),
	FOODPOISONING	UMETA(DisplayName = "FOODPOISONING")
};

USTRUCT(BlueprintType)
struct FUnusualConditionData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "NoahCharacter")
		ENoahUnusualCondition StateName;
	UPROPERTY(BlueprintReadOnly, Category = "NoahCharacter")
		float LifeSpan;
	UPROPERTY(BlueprintReadOnly, Category = "NoahCharacter")
		float Figure;//캐릭터 스텟에 영향미칠 수치
};

UCLASS()
class NOAH_API ANoahCharacter : public ACharacter
{
	GENERATED_BODY()
private:
	//카메라 줌이 가능한 최대값과 최소값
	int m_zoomMax;
	int m_zoomMin;
public:
	UPROPERTY(BlueprintReadWrite, Category = "NoahCharacter")
		UInventory* Inventory;
	UPROPERTY(BlueprintReadWrite, Category = "NoahCharacter")
		UCraft* Craft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
public:
	// Sets default values for this character's properties
	ANoahCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUpAtRate(float Rate);
	void TurnAtRate(float Rate);
	void CameraZoomRate(float Rate);
	void Attack();
	void StopAttack();
	void Jump();
	void StopJumping();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Object Detect
public:
	UPROPERTY(BlueprintReadWrite, Category = "NoahCharacter")
		ENoahState NoahState;

	//장비
	UPROPERTY(BlueprintReadWrite, Category = "NoahCharacter")
		AItem* RightEquipmentItem;
	UPROPERTY(BlueprintReadWrite, Category = "NoahCharacter")
		bool LeftEquipmentItem;


	//상태
	UPROPERTY(BlueprintReadWrite, Category = "NoahCharacter")
		float MaxHP;
	UPROPERTY(BlueprintReadWrite, Category = "NoahCharacter")
		float HP;

	UPROPERTY(BlueprintReadWrite, Category = "NoahCharacter")
		float MaxHungry;
	UPROPERTY(BlueprintReadWrite, Category = "NoahCharacter")
		float Hungry;

	UPROPERTY(BlueprintReadWrite, Category = "NoahCharacter")
		float MaxTired;
	UPROPERTY(BlueprintReadWrite, Category = "NoahCharacter")
		float Tired;

	//상태이상
private:
	float UnusualConditionTickTime; //데미지 적용 시간제한용 변수
	float HPUnusualCondition; //HP 감소에 반영될 상태이상 수치
	void  UnusualCondition(float DeltaTime); //Tick마다 체크
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "NoahCharacter")
		TArray<FUnusualConditionData> UnusualConditionArray; //상태이상 컨테이너

	UFUNCTION(BlueprintCallable, Category = "NoahCharacter")
		void AddUnusualCondition(ENoahUnusualCondition AddCondition); //상태이상 추가

	//오브젝트 탐색
private:
	TArray<AActor*> DetectedObject;

public:
	UFUNCTION(BlueprintCallable, Category = "NoahCharacter")
		bool DetectObject(AActor* detectedObject); //탐색 오브젝트 입력
	UFUNCTION(BlueprintCallable, Category = "NoahCharacter")
		bool MissObject(AActor* missedObject); //오브젝트 제거
	UFUNCTION(BlueprintCallable, Category = "NoahCharacter")
		AActor* FindNearItem(); //가장 가까운 아이템 검색

	//아이템 착용
	UFUNCTION(BlueprintCallable, Category = "NoahCharacter")
		void EquipItem(AItem* _Item);
	UFUNCTION(BlueprintCallable, Category = "NoahCharacter")
		TSubclassOf<class UObject> LoadBluePrintClass(FString name);
	//아이템 소비
	UFUNCTION(BlueprintCallable, Category = "NoahCharacter")
		bool ConsumeItem(AItem* _Item, ENoahUnusualCondition _Condition);

	//데미지 받기
	UFUNCTION(BlueprintCallable, Category = "NoahCharacter")
		float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);

	//블루프린트 불러오기
	UFUNCTION(BlueprintCallable, Category = "NoahCharacter")
		UBlueprintGeneratedClass* GetBlueprint(FString Path);
};
