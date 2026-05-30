#include "RogueCharacter.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ARogueCharacter::ARogueCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	//Camera
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation=true;
	
	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
}

void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();
}



void ARogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARogueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input=Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(InputMove,ETriggerEvent::Triggered,this,&ARogueCharacter::Move);
	Input->BindAction(InputLook,ETriggerEvent::Triggered,this,&ARogueCharacter::Look);
	
}

void ARogueCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D Value=InputValue.Get<FVector2D>();
	
	//Froward/Backward Direction
	FRotator ControllerRotation=GetControlRotation();
	ControllerRotation.Pitch=0;
	ControllerRotation.Roll=0;
	AddMovementInput(ControllerRotation.Vector(),Value.X);
	
	//Right/Left Direction
	FVector RightDirection=GetActorRightVector();
	AddMovementInput(RightDirection,Value.Y);
}

void ARogueCharacter::Look(const FInputActionValue& InputValue)
{
    FVector2D Value=InputValue.Get<FVector2D>();
	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}