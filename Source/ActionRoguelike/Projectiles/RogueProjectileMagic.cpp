

#include "RogueProjectileMagic.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ARogueProjectileMagic::ARogueProjectileMagic()
{
	SphereComponent=CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(16.f);
	SphereComponent->SetCollisionProfileName(TEXT("Projectile"));
	
	LoopingNiagaraComponent=CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopingNiagaraComponent"));
	LoopingNiagaraComponent->SetupAttachment(SphereComponent);
	
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed=2000.f;
	ProjectileMovementComponent->ProjectileGravityScale=0.f;
	
	LoopingSoundComponent=CreateDefaultSubobject<UAudioComponent>(TEXT("LoopingSoundComponent"));
	LoopingSoundComponent->SetupAttachment(SphereComponent);
}


void ARogueProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentHit.AddDynamic(this,&ARogueProjectileMagic::OnActorHit);
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(),true);
}

void ARogueProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	FVector HitFromDirection = GetActorRotation().Vector();;
	UGameplayStatics::ApplyPointDamage(OtherActor,10.f,HitFromDirection,Hit,GetInstigatorController(),this,DamageTypeClass);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ExplosionEffect,GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this,ExplosionSound,GetActorLocation());
	Destroy();
}