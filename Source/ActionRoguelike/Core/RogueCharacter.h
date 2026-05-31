#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RogueCharacter.generated.h"

class UNiagaraSystem;
class ARogueProjectileMagic;
struct FInputActionValue;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;

UCLASS()
class ACTIONROGUELIKE_API ARogueCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARogueCharacter();

protected:
	
	UPROPERTY(EditDefaultsOnly,Category="PrimaryAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly,Category="PrimaryAttack")
	TObjectPtr<USoundBase> CastingSound;
	
	UPROPERTY(EditDefaultsOnly,Category="PrimaryAttack")
	TObjectPtr<UAnimMontage> PrimaryAttackAnimMontage;
	
	UPROPERTY(EditDefaultsOnly,Category="PrimaryAttack")
	TSubclassOf<ARogueProjectileMagic> ProjectileMagicClass;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> InputMove;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> InputLook;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> InputPrimaryAttack;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> InputJump;
	
	UPROPERTY(VisibleAnywhere,Category="Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere,Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere,Category="PrimaryAttack")
	FName PrimaryAttackSocketName;
	
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void PrimaryAttack();
	void PrimaryAttackTimerElapsed();
	

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
