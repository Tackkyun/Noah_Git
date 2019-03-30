// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "NoahGameModeBase.h"

ANoahGameModeBase::ANoahGameModeBase()
{
	//GameMode -> Dafault Pawn Class Setting
	static ConstructorHelpers::FClassFinder<APawn>
		PlayerPawn(TEXT("Blueprint'/Game/GameMode/BP_NoahCharacter'"));
	if (PlayerPawn.Succeeded()) {
		DefaultPawnClass = PlayerPawn.Class;
	}
	//GameMode -> Player Controller Class Setting
	static ConstructorHelpers::FClassFinder<APlayerController>
		PlayerController(TEXT("Blueprint'/Game/GameMode/BP_NoahPlayerController'"));
	if (PlayerController.Succeeded())
	{
		PlayerControllerClass = PlayerController.Class;
	}
	//GameMode -> Player State Setting
	static ConstructorHelpers::FClassFinder<APlayerState>
		PlayerState(TEXT("Blueprint'/Game/GameMode/BP_NoahPlayerState'"));
	if (PlayerState.Succeeded())
	{
		PlayerStateClass = PlayerState.Class;
	}
	//GameMode -> HUD Setting
	static ConstructorHelpers::FClassFinder<AHUD>
		HUD(TEXT("Blueprint'/Game/GameMode/BP_NoahHUD'"));
	if (HUD.Succeeded())
	{
		HUDClass = HUD.Class;
	}
	//GameMode -> GameStateBase Setting
	static ConstructorHelpers::FClassFinder<AGameStateBase>
		GameStateBase(TEXT("Blueprint'/Game/GameMode/BP_NoahGameStateBase'"));
	if (GameStateBase.Succeeded())
	{
		GameStateClass = GameStateBase.Class;
	}
}