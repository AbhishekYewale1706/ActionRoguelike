
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueExplosiveBarrel.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class URadialForceComponent;
class UAudioComponent;
class USoundBase;

UCLASS()
class ACTIONROGUELIKE_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category= "Explosive Barrel")
	float ExplosionDelay = 3.0f;
	
	UPROPERTY(EditDefaultsOnly,Category="Explosive Barrel")
	TObjectPtr<UNiagaraSystem> ExplodeEffect;
	
	UPROPERTY(EditDefaultsOnly,Category="Explosive Barrel")
	TObjectPtr<USoundBase> ExplodeSound;
	
	UPROPERTY(EditDefaultsOnly,Category="Explosive Barrel")
	TObjectPtr<UNiagaraSystem> loopingBurningEffect;
	
	UPROPERTY(EditDefaultsOnly,Category="Explosive Barrel")
	TObjectPtr<USoundBase> loopingBurningSound;
	
	UPROPERTY(VisibleAnywhere,Category="Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(EditDefaultsOnly,Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> ActiveBurningSound=nullptr;
	
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveBurningEffect=nullptr;
	
	
	bool bExploded = false;
	FTimerHandle ExplosionTimerHandle;
	void ApplyDamage();
	
public:
	ARogueExplosiveBarrel();
	virtual  float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
};