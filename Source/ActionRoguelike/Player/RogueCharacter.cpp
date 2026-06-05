#include "RogueCharacter.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ActionRoguelike/Projectiles/RogueBlackHoleProjectile.h"
#include "ActionRoguelike/Projectiles/RogueProjectileMagic.h"
#include "ActionRoguelike/Projectiles/RogueTeleportProjectile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ARogueCharacter::ARogueCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	//Camera
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation=true;
	
	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	PrimaryAttackSocketName="Muzzle_01";
	
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
	Input->BindAction(InputPrimaryAttack,ETriggerEvent::Triggered,this,&ARogueCharacter::PrimaryAttack);
	Input->BindAction(InputJump,ETriggerEvent::Triggered,this,&ARogueCharacter::Jump);
	Input->BindAction(InputJump,ETriggerEvent::Completed,this,&ARogueCharacter::StopJumping);
	Input->BindAction(InputBlackHoleAbility,ETriggerEvent::Triggered,this,&ARogueCharacter::BlackHoleAbility);
	Input->BindAction(InputTeleportAbility,ETriggerEvent::Triggered,this,&ARogueCharacter::TeleportAbility);
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

void ARogueCharacter::PrimaryAttack()
{
	PlayAnimMontage(PrimaryAttackAnimMontage);
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect,GetMesh(),PrimaryAttackSocketName,FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::Type::SnapToTarget,true);
	UGameplayStatics::PlaySound2D(this,CastingSound);
	
	FTimerHandle PrimaryAttackTimeHandle;
	float AttackDelayTime =0.2f;
	GetWorldTimerManager().SetTimer(PrimaryAttackTimeHandle,this,&ARogueCharacter::PrimaryAttackTimerElapsed,AttackDelayTime);
	
}
void ARogueCharacter::PrimaryAttackTimerElapsed()
{
	FVector SpawnLocation=GetMesh()->GetSocketLocation(PrimaryAttackSocketName);
	FRotator SpawnRotation=GetControlRotation();
	FActorSpawnParameters SpawnParam;
	SpawnParam.Instigator=this;
	SpawnParam.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* NewProjectile=GetWorld()->SpawnActor<AActor>(ProjectileMagicClass,SpawnLocation,SpawnRotation,SpawnParam);
	MoveIgnoreActorAdd(NewProjectile);
}

void ARogueCharacter::BlackHoleAbility()
{
	PlayAnimMontage(PrimaryAttackAnimMontage);
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect,GetMesh(),PrimaryAttackSocketName,FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::Type::SnapToTarget,true);
	UGameplayStatics::PlaySound2D(this,CastingSound);
	FTimerHandle PrimaryAttackTimeHandle;
	float AttackDelayTime =0.2f;
	GetWorldTimerManager().SetTimer(PrimaryAttackTimeHandle,this,&ARogueCharacter::BlackHoleTimerElapsed,AttackDelayTime);
}

void ARogueCharacter::BlackHoleTimerElapsed()
{
	FVector SpawnLocation=GetMesh()->GetSocketLocation(PrimaryAttackSocketName);
	FRotator SpawnRotation=GetControlRotation();
	FActorSpawnParameters SpawnParam;
	SpawnParam.Instigator=this;
	SpawnParam.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* NewProjectile=GetWorld()->SpawnActor<AActor>(ProjectileBlackHoleClass,SpawnLocation,SpawnRotation,SpawnParam);
	MoveIgnoreActorAdd(NewProjectile);
}

void ARogueCharacter::TeleportAbility()
{
	PlayAnimMontage(PrimaryAttackAnimMontage);
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect,GetMesh(),PrimaryAttackSocketName,FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::Type::SnapToTarget,true);
	UGameplayStatics::PlaySound2D(this,CastingSound);
	FTimerHandle PrimaryAttackTimeHandle;
	float AttackDelayTime =0.2f;
	GetWorldTimerManager().SetTimer(PrimaryAttackTimeHandle,this,&ARogueCharacter::TeleportTimerElapsed,AttackDelayTime);
}

void ARogueCharacter::TeleportTimerElapsed()
{
	FVector SpawnLocation=GetMesh()->GetSocketLocation(PrimaryAttackSocketName);
	FRotator SpawnRotation=GetControlRotation();
	FActorSpawnParameters SpawnParam;
	SpawnParam.Instigator=this;
	SpawnParam.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* NewProjectile=GetWorld()->SpawnActor<AActor>(ProjectileTeleportClass,SpawnLocation,SpawnRotation,SpawnParam);
	MoveIgnoreActorAdd(NewProjectile);
	
}
