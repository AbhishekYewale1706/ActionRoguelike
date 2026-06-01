#pragma once

#include "CoreMinimal.h"
#include "ActionRoguelike/Interface/RogueInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "RogueItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueItemChest : public AActor, public IRogueInteractionInterface

{
	GENERATED_BODY()



protected:
	UPROPERTY(VisibleAnywhere,Category="Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;
	
	UPROPERTY(VisibleAnywhere,Category="Components")
	TObjectPtr<UStaticMeshComponent> ChildMeshComponent;
	
	UPROPERTY(EditDefaultsOnly,Category="Animation")
	float AnimationSpeed=50.0f;
	
	UPROPERTY(EditDefaultsOnly,Category="Animation")
	float TargetPitch=120.0f;
	
	UPROPERTY(VisibleDefaultsOnly,Category="Animation")
	float CurrentPitch=0.0f;

public:
	ARogueItemChest();
	virtual void Tick(float DeltaTime) override;
	virtual void OnInteraction() override;
	
};
