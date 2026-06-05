
#pragma once

#include "CoreMinimal.h"
#include "RogueProjectileBase.h"
#include "RogueBlackHoleProjectile.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueBlackHoleProjectile : public ARogueProjectileBase
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly,Category="BlackHolePower")
	float Radius = 1200.0f;
	
	UPROPERTY(EditDefaultsOnly,Category="BlackHolePower")
	float ForceStrength=-800000.0f;
	
	UPROPERTY(EditDefaultsOnly,Category="BlackHolePower")
	float LifeTime=5.0f;
	
	UPROPERTY(EditDefaultsOnly,Category="Components")
	TObjectPtr<URadialForceComponent>RadialForceComponent;
	
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
    
public:
	virtual void PostInitializeComponents() override;
	ARogueBlackHoleProjectile();
};
