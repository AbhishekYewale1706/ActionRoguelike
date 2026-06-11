
#include "RogueActionSystemComponent.h"


URogueActionSystemComponent::URogueActionSystemComponent()
{
	
}

void URogueActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	float OldHealth=Attributes.Health;
	float MaxHealth=GetDefault<URogueActionSystemComponent>()->Attributes.Health;
	
	Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.0f, MaxHealth);
	
	if (!FMath::IsNearlyEqual(OldHealth,Attributes.Health))
	{
		OnHealthChanged.Broadcast(Attributes.Health,OldHealth);
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,FString::Printf(TEXT("Health: %f"),Attributes.Health));
	}
	
}