#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RogueCharacter.generated.h"

struct FInputActionValue;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARogueCharacter();

protected:
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> InputMove;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> InputLook;
	
	UPROPERTY(VisibleAnywhere,Category="Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere,Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
