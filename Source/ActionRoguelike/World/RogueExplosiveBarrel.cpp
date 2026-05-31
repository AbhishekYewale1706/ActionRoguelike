
#include "RogueExplosiveBarrel.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"



ARogueExplosiveBarrel::ARogueExplosiveBarrel()
{
	MeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionProfileName("PhysicsActor");
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetupAttachment(RootComponent);
	
	RadialForceComponent=CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(MeshComponent);
	RadialForceComponent->ImpulseStrength = 150000.0f;
	RadialForceComponent->Radius = 750.f;
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = true;
	
}

float ARogueExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (bExploded || GetWorldTimerManager().TimerExists(ExplosionTimerHandle))
	{
		return ActualDamage;
	}
	
	//Attaching the Niagara System and SoundBase to the Component at runtime
	ActiveBurningEffect=UNiagaraFunctionLibrary::SpawnSystemAttached(loopingBurningEffect,MeshComponent,NAME_None,FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::Type::SnapToTarget,true);
	ActiveBurningSound=UGameplayStatics::SpawnSoundAttached(loopingBurningSound,MeshComponent);
	GetWorldTimerManager().SetTimer(ExplosionTimerHandle,this,&ARogueExplosiveBarrel::ApplyDamage,ExplosionDelay);
	return ActualDamage;
	
}

void ARogueExplosiveBarrel::ApplyDamage()
{
	bExploded=true;
	ActiveBurningEffect->Deactivate();
	ActiveBurningSound->Stop();
	RadialForceComponent->FireImpulse();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ExplodeEffect,GetActorLocation(),GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this,ExplodeSound,GetActorLocation(),GetActorRotation());
}
