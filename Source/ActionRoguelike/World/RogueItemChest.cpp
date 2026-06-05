
#include "RogueItemChest.h"


ARogueItemChest::ARogueItemChest()
{
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	BaseMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	BaseMeshComponent->SetCollisionProfileName("Interaction");
	RootComponent=BaseMeshComponent;
	
	ChildMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChildMeshComponent"));
	ChildMeshComponent->SetCollisionProfileName("NoCollision");
	ChildMeshComponent->SetupAttachment(BaseMeshComponent);
}

void ARogueItemChest::OnInteraction_Implementation()
{
	//IRougeInteractionInterface function
	SetActorTickEnabled(true);
}


void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentPitch=FMath::FInterpConstantTo(CurrentPitch,TargetPitch,DeltaTime,AnimationSpeed);
	ChildMeshComponent->SetRelativeRotation(FRotator(CurrentPitch,0,0));
	
	if (FMath::IsNearlyEqual(CurrentPitch,TargetPitch))
	{
		//Chest Animation Completed
		SetActorTickEnabled(false);
		 ChestAnimationCompleted();
	}
	
}


