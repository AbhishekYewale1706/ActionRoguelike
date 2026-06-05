
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraComponent;
class UAudioComponent;
class UNiagaraSystem;
class USoundBase;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueProjectileBase : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly,Category="Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditDefaultsOnly,Category="Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(EditDefaultsOnly,Category="Components")
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
	
	UPROPERTY(EditDefaultsOnly,Category="Components")
	TObjectPtr<UNiagaraComponent> LoopingNiagaraComponent;
	
	UPROPERTY(EditDefaultsOnly,Category="Damage")
	TSubclassOf<UDamageType>DamageTypeClass;
	
	UPROPERTY(EditDefaultsOnly,Category="Effects")
	TObjectPtr<UNiagaraSystem>ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly,Category="Sound")
	TObjectPtr<USoundBase>ExplosionSound;
	
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit);
	
	
public:
	virtual void PostInitializeComponents() override;
	ARogueProjectileBase();
	
	void PlaySoundAndEffect();
};
