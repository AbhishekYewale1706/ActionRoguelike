// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePlayerController.h"

#include "EnhancedInputComponent.h"
#include "RogueInteractionComponent.h"


ARoguePlayerController::ARoguePlayerController()
{
	InteractionComponent=CreateDefaultSubobject<URogueInteractionComponent>(TEXT("InteractionComp"));
}

void ARoguePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* Input=Cast<UEnhancedInputComponent>(InputComponent);
	Input->BindAction(Input_Interact,ETriggerEvent::Triggered,this,&ARoguePlayerController::StartInteraction);
	
}
void ARoguePlayerController::StartInteraction()
{
	InteractionComponent->InteractBestActor();
}
