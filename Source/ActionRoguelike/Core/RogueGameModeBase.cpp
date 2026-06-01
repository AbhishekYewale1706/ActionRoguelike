// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueGameModeBase.h"

#include "ActionRoguelike/Player/RoguePlayerController.h"

ARogueGameModeBase::ARogueGameModeBase()
{
	PlayerControllerClass=ARoguePlayerController::StaticClass();
}
