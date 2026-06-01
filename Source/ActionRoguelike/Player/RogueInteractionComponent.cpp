
#include "RogueInteractionComponent.h"
#include "ActionRoguelike/RogueGameType.h"
#include "ActionRoguelike/Interface/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"



URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URogueInteractionComponent::InteractBestActor()
{
	IRogueInteractionInterface* RefInteractionInterface=Cast<IRogueInteractionInterface>(SelectedActor);
	if (RefInteractionInterface)
	{
		RefInteractionInterface->OnInteraction();
	}
}

void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Ref for PlayerController
	APlayerController* PC=CastChecked<APlayerController>(GetOwner());
	FVector Center = PC->GetPawn()->GetActorLocation();
	
	//Create a Sphere around character
	TArray<FOverlapResult> Overlaps;
	ECollisionChannel TraceChannel = ECollisionChannel::COLLISION_INTERACTION;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(InteractionRange);
	GetWorld()->OverlapMultiByChannel(Overlaps,Center,FQuat::Identity,TraceChannel,CollisionShape);
	DrawDebugSphere(GetWorld(), Center, InteractionRange, 10, FColor::White);
	
	//Best Result
	AActor* BestActor=nullptr;
	float BestDistance=-1.f;
	
	//Getting for the Overlap Result
	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation=Overlap.GetActor()->GetActorLocation();
		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);
		
		FVector OverlapDirection=OverlapLocation-Center;
		OverlapDirection.Normalize();
		float DotProduct=FVector::DotProduct(OverlapDirection,PC->GetControlRotation().Vector());
		
		FString PrintDotProductResult=FString::Printf(TEXT("DotProduct: %f"),DotProduct);
		DrawDebugString(GetWorld(),OverlapLocation,PrintDotProductResult,nullptr,FColor::White,0.0f,true);
		
		if (DotProduct>BestDistance)
		{
			BestActor=Overlap.GetActor();
			BestDistance=DotProduct;
		}
	}
	
	SelectedActor=BestActor;
	if (BestActor)
	{
		DrawDebugSphere(GetWorld(), BestActor->GetActorLocation(), 60.f, 10, FColor::Green);
	}
}

