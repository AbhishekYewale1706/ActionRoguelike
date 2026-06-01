
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueInteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
protected:

	  UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	  float InteractionRange = 550.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TObjectPtr<AActor> SelectedActor;
public:
	void InteractBestActor();
	
	URogueInteractionComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
