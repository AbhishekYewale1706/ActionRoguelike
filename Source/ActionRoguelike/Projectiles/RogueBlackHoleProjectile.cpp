
#include "RogueBlackHoleProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARogueBlackHoleProjectile::ARogueBlackHoleProjectile()
{
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->ForceStrength = ForceStrength; 
	RadialForceComponent->Radius = Radius;
	
	// Avoid sucking player into the blackhole
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	SphereComponent->SetSphereRadius(30.0f);
	SphereComponent->SetCollisionProfileName("BlackholeCore");
	ProjectileMovementComponent->InitialSpeed = 500.0f;
	
	InitialLifeSpan = LifeTime;
}

void ARogueBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
}



void ARogueBlackHoleProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARogueBlackHoleProjectile::OnSphereOverlappedActor);
}

void ARogueBlackHoleProjectile::OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}