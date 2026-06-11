
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"


USTRUCT(BlueprintType)
struct FRogueActionAttributes
{
	GENERATED_BODY()
	
	FRogueActionAttributes()
	{
		Health = 100.0f;
	}
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Attributes")
	float Health;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged,float,NewHealth,float,OldHealth);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Attributes")
		FRogueActionAttributes Attributes;
	
	   
public:
	
	void ApplyHealthChange(float InValueChange);
	URogueActionSystemComponent();

	UPROPERTY(BlueprintAssignable,Category = "Attributes")
	FOnHealthChanged OnHealthChanged;
};
